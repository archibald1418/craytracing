#include "minirt.h"

int	check_tokens(char ***tokens, int len, char *token_name, char *unit)
{
	int	i;

	(void)token_name;
	(void)len;
	(void)unit;
	i = 0;
	while ((*tokens)[i] != NULL)
		if (++i > len)
			return (handle_errors("TOO MANY TOKENS!\n"));
	if (i < len)
		return (handle_errors("TOO FEW TOKENS!\n"));
	return (1);
}

int	check_fov(int fov)
{
	if (!(0 < fov && fov <= 180))
		return (handle_errors("FOV NOT IN RANGE [0, 180]\n"));
	return (1);
}

int	check_point(char ***tokens, t_p3d *p, int is_normal)
{
	const char	*msgs[] = {"POINT", "NORMAL"};
	double		x;
	double		y;
	double		z;

	if (check_tokens(tokens, 3, "COORD", (char *)(msgs[is_normal])) != 1)
		return (handle_errors("POINT ERROR RLY??¯\\_(ツ)_/¯\n"));
	x = (double)ft_atof((*tokens)[0]);
	y = (double)ft_atof((*tokens)[1]);
	z = (double)ft_atof((*tokens)[2]);
	if (isnan(x))
		return (handle_errors("BAD X COORD \n"));
	if (isnan(y))
		return (handle_errors("BAD Y COORD !\n"));
	if (isnan(z))
		return (handle_errors("BAD Z COORD !\n"));
	if (is_normal)
		if (x == 0 && y == 0 && z == 0)
			return (handle_errors("ZERO NORMAL ERROR ¯\\_(ツ)_/¯\n"));
	init_p3d(p, x, y, z);
	free_arr((void **)*tokens, 3);
	return (1);
}

void	parse_location(char ***ploc, t_p3d *loc, char **tokens)
{
	*ploc = ft_strsplit(tokens[1], ",");
	if (!(*ploc))
		handle_errors("Malloc error...\n");
	if (check_point(ploc, loc, 0) != 1)
		handle_errors("LOCATION ERROR ¯\\_(ツ)_/¯\n");
}

void	parse_direction(char ***pdir, t_p3d *dir2, char **tokens)
{
	*pdir = ft_strsplit(tokens[2], ",");
	if (!(*pdir))
		handle_errors("Malloc error...\n");
	if (check_point(pdir, dir2, 1) != 1)
		handle_errors("DIRECTION ERROR ¯\\_(ツ)_/¯\n");
}

int	check_cam (char **tokens, t_cam *cam)
{
	t_p3d	loc;
	t_p3d	dir1;
	t_p3d	dir2;
	char	**ploc;
	char	**pdir;

	if (check_tokens(&tokens, 4, "ELEMENT", "CAMERA") != 1)
		return (handle_errors("CAMERA ERROR ¯\\_(ツ)_/¯\n"));
	parse_location(&ploc, &loc, tokens);
	parse_direction(&pdir, &dir2, tokens);
	cam->fov = (double)ft_atof(tokens[3]);
	if (isnan(cam->fov))
		return (handle_errors("BAD FOV ...\n"));
	if (!check_fov((int)cam->fov))
		return (handle_errors("FOV ERROR ...\n"));
	normalize(&dir1, dir2);
	init_camera(cam, loc, dir1, cam->fov);
	return (1);
}

int	check_res (char **tokens, t_rt *rt)
{
	double	X;
	double	Y;

	if (rt->has_res)
		return (handle_errors("RESOLUION IS ALREADY SET! \\_(-_-)_/\n"));
	if (check_tokens(&tokens, 3, "ELEMENT", "RESOLUTION") != 1)
		return (handle_errors("RESOLUTION ERROR ¯\\_(ツ)_/¯\n"));
	X = (double)ft_atoi(tokens[1]);
	if (isnan(X) || (int)X <= 0)
		return (handle_errors("BAD WINDOW WIDTH >_<\n"));
	Y = (double)ft_atoi(tokens[2]);
	if (isnan(Y) || (int)Y <= 0)
		return (handle_errors("BAD WINDOW HEIGHT >_<\n"));
	rt->res.X = (int)X;
	rt->res.Y = (int)Y;
	rt->has_res = 1;
	return (1);
}

int	check_rgb(char ***tokens, t_color *color)
{
	double	r;
	double	g;
	double	b;

	if (check_tokens(tokens, 3, "COLOR", "RGB") != 1)
		return (0);
	r = (double)ft_atof((*tokens)[0]);
	if (isnan(r) || (int)r < 0 || (int)r > 255)
		return (0);
	g = (double)ft_atof((*tokens)[1]);
	if (isnan(g) || (int)g < 0 || (int)g > 255)
		return (0);
	b = (double)ft_atof((*tokens)[2]);
	if (isnan(b) || (int)b < 0 || (int)b > 255)
		return (0);
	if (r - (double)((int)r) > 0.0 || g - (double)((int)g) > 0.0 || \
		b - (double)((int)b) > 0.0)
		return (handle_errors("COLOR MUST BE AN INT! OH BOI\n"));
	set_color(color, (int)r, (int)g, (int)b);
	free_arr((void **)*tokens, 3);
	return (1);
}

int	check_lamb(char **tokens, t_rt *rt)
{
	double	lum;
	char	**rgb;
	t_color	color;

	if (rt->has_lamb)
		return (handle_errors("AMBIENCE IS ALREADY SET!\n"));
	if (check_tokens(&tokens, 3, "ELEMENT", "AMBIENCE") != 1)
		return (handle_errors("AMBIENCE ERROR... \n"));
	lum = (double)ft_atof(tokens[1]);
	if (isnan(lum))
		return (handle_errors("BAD LUMINANCE!\n"));
	if (lum < 0 || lum > 1)
		return (handle_errors("LUMINANCE OUT OF RANGE [0,1]\n"));
	rgb = ft_strsplit(tokens[2], ",");
	if (!(rgb))
		return (handle_errors("Malloc errror"));
	if (check_rgb(&rgb, &color) != 1)
		return (handle_errors("BAD AMBIENT COLOR!\n"));
	set_lamb(&rt->lamb, lum, &color);
	rt->has_lamb = 1;
	return (1);
}

int	check_lsrc(char **tokens, t_lsrc *lsrc)
{
	double	lum;
	char	**rgb;
	char	**ploc;

	if (check_tokens(&tokens, 4, "ELEMENT", "LIGHT SOURCE") != 1)
		return (handle_errors("LIGHT ERROR... \n"));
	lum = (double)ft_atof(tokens[2]);
	if (isnan(lum))
		return (handle_errors("BAD LUMINANCE!\n"));
	if (lum < 0 || lum > 1)
		return (handle_errors("LUMINANCE OUT OF RANGE [0,1]\n"));
	lsrc->lum = lum;
	rgb = ft_strsplit(tokens[3], ",");
	if (!(rgb))
		return (-1);
	if (check_rgb(&rgb, &lsrc->col) != 1)
		return (handle_errors("BAD LIGHT COLOR!\n"));
	parse_location(&ploc, &lsrc->loc, tokens);
	return (1);
}

int	check_posdir(char **tokens, t_p3d *l, t_p3d *d, char *type)
{
	char	**ploc;
	char	**pdir;

	(void)type;
	parse_location(&ploc, l, tokens);
	if (d != NULL)
		parse_direction(&pdir, d, tokens);
	return (1);
}

int			check_pl(char **tokens, t_rt *rt)
{
	t_pl	pl;
	t_p3d	tmp;
	char	**rgb;
	t_pl	*out;
	
	if (check_tokens(&tokens, 4, "ELEMENT", "PLANE") != 1)
		return (handle_errors("PLANE ERROR... \n"));	
	if (check_posdir(tokens, &pl.p, &tmp, "PLANE") != 1)
		return (handle_errors("PLANE ERROR...\n"));
	if (!(rgb = ft_strsplit(tokens[3], ",")))
		return (-1);
	if (check_rgb(&rgb, &pl.color) != 1)
		return (handle_errors("PLANE COLOR ERROR...\n"));

	normalize(&pl.dir, tmp);
	if (!(out = ft_memdup(&pl, sizeof(t_pl))))
		return (handle_errors("Malloc error...\n"));
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, PL, 4);
	return (1);
}

int		check_sp(char **tokens, t_rt *rt)
{
	t_sp sp;
	char	**rgb;
	char	**ploc;

	if (check_tokens(&tokens, 4, "ELEMENT", "SP") != 1)
		return (handle_errors("SPHERE ERROR... \n"));
	// Check diameter
	if (isnan(sp.d = (double)ft_atof(tokens[2])) || sp.d <= 0)
		return (handle_errors("SPHERE DIAMETER MUST BE POSITIVE!\n"));

	// Check center
	if (!(ploc = ft_strsplit(tokens[1], ",")))
		return (-1);
	if (check_point(&ploc, &sp.c, 0) != 1)
		return (handle_errors("SPHERE CENTER ERROR\n"));

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[3], ",")))
		return (-1);
	if (check_rgb(&rgb, &sp.color) != 1)
		return (handle_errors("SPHERE COLOR ERROR\n"));

	// Copy sphere to array
	if (!(rt->shapes.shapes[rt->shapes.top].shape = ft_memdup(&sp, sizeof(t_sp))))
		return (-1);
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, SP, 4);
	return (1);
}

int		check_sq(char **tokens, t_rt *rt)
{
	t_sq sq;
	char	**rgb;
	double size;
	t_sq *out;

	if (check_tokens(&tokens, 5, "ELEMENT", "SQUARE") != 1)
		return (handle_errors("SQUARE ERROR... \n"));
	// Check size
	if (isnan(size = (double)ft_atof(tokens[3])) || size <= 0)
		return (handle_errors("SQUARE SIZE MUST BE POSITIVE!\n"));
	sq.size = size;

	// Check center & normal
	if (check_posdir(tokens, &sq.c, &sq.dir, "SQUARE") != 1)
		return (handle_errors("SQUARE ERROR...\n"));

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[4], ",")))
		return (-1);
	if (check_rgb(&rgb, &sq.color) != 1)
		return (handle_errors("SQUARE COLOR ERROR\n"));

	// Copy square to array
	if (!(out = ft_memdup(&sq, sizeof(t_sq))))
		return (-1);
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, SQ, 4);
	return (1);
}

int		check_tr(char **tokens, t_rt *rt)
{
	t_tr tr;
	char	**arr;
	t_tr *out;

	if (check_tokens(&tokens, 5, "ELEMENT", "TRIANGLE") != 1)
		return (handle_errors("TRIANGLE ERROR... \n"));
	// Check points
	if (check_posdir(tokens, &tr.A, NULL, "TRIANGLE") != 1 || \
		check_posdir(tokens + 1, &tr.B, NULL, "TRIANGLE") != 1 || \
		check_posdir(tokens + 2, &tr.C, NULL, "TRIANGLE") != 1)
		return (handle_errors("TRIANGLE POINT ERROR...\n"));

	// Check rgb
	if (!(arr = ft_strsplit(tokens[4], ",")))
		return (-1);
	if (check_rgb(&arr, &tr.color) != 1)
		return (handle_errors("TRIANGLE COLOR ERROR...\n"));

	// Copy triangle to array
	if (!(out = ft_memdup(&tr, sizeof(t_tr))))
		return (-1);
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, TR, 4);
	return (1);
}

int		check_cy(char **tokens, t_rt *rt)
{
	t_cy cy;
	char **rgb;
	t_cy *out;

	if (check_tokens(&tokens, 6, "ELEMENT", "CYLINDER") != 1)
		return (handle_errors("PLANE CYLINDER... \n"));
	// Check diameter
	if (isnan(cy.d = (double)ft_atof(tokens[3])) || cy.d <= 0)
		return (handle_errors("CYLINDER DIAMETER MUST BE POSITIVE!\n"));	

	// Check height
	if (isnan(cy.h = (double)ft_atof(tokens[4])) || cy.h <= 0)
		return (handle_errors("CYLINDER HEIGHT MUST BE POSITIVE!\n"));

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[5], ",")))
		return (-1);
	if (check_rgb(&rgb, &cy.color) != 1)
		return (handle_errors("CYLINDER COLOR ERROR...\n"));

	// Check posdir
	if (check_posdir(tokens, &cy.c, &cy.dir, "CYLINDER") != 1)
		return (handle_errors("CYLINDER POINT ERROR...\n"));

	// Copy cylinder to array
	if (!(out = ft_memdup(&cy, sizeof(t_cy))))
		return (-1);
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, CY, 4);
	return (1);
}

