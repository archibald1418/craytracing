#include "minirt.h"

int		check_tokens(char ***tokens, int len, char *token_name, char *unit)
{
	int i;

	i = 0;
	while ((*tokens)[i] != NULL)
		if (++i > len)
			return (dprintf(1, "TOO MANY %sS IN %s!\n", token_name, unit));
	if (i < len)
		return (dprintf(1, "TOO FEW %sS IN %s!\n", token_name, unit));
	return (1);
}

int		check_fov(int fov)
{
	if (!(0 <= fov && fov <= 180))
		return (dprintf(1, "FOV NOT IN RANGE [0, 180]\n"));
	// TODO: check zero fov at raycasting stage
	return (1);
}

int		check_point(char ***tokens, t_p3d *p, int is_normal)
{
	const char *msgs[] = {"POINT", "NORMAL"};
	double x;
	double y;
	double z;

	if (check_tokens(tokens, 3, "COORD", (char *)(msgs[is_normal])) != 1)
		return (dprintf(1, "%s ERROR ¯\\_(ツ)_/¯\n", msgs[is_normal]));
	if (isnan(x = (double)ft_atof((*tokens)[0])))
		return (dprintf(1, "BAD X COORD IN %s!\n", msgs[is_normal]));
	if (isnan(y = (double)ft_atof((*tokens)[1])))
		return (dprintf(1, "BAD Y COORD IN %s!\n", msgs[is_normal]));
	if (isnan(z = (double)ft_atof((*tokens)[2])))
		return (dprintf(1, "BAD Z COORD IN %s!\n", msgs[is_normal]));
	if (is_normal)
		if (x == 0 && y == 0 && z == 0)
			return (dprintf(1, "ZERO NORMAL ERROR ¯\\_(ツ)_/¯\n"));
	init_p3d(p, x, y, z);
	free_arr((void**)*tokens, 3);
	return (1);
	//
}

int		check_cam (char **tokens, t_cam *cam)
{
	int i;
	t_p3d loc;
	t_p3d dir1;
	t_p3d dir2;
	double fov;
	char **ploc;
	char **pdir;

	i = 0;
	if (check_tokens(&tokens, 4, "ELEMENT", "CAMERA") != 1)
		return (dprintf(1, "CAMERA ERROR ¯\\_(ツ)_/¯\n"));

	// Parse location
	if (!(ploc = ft_strsplit(tokens[1], ",")))
		return (-1);
	if (check_point(&ploc, &loc, 0) != 1)
		return (dprintf(1, "CAMERA LOCATION ERROR ¯\\_(ツ)_/¯\n"));

	// Parse direction
	if (!(pdir = ft_strsplit(tokens[2], ",")))
		return (-1);
	if (check_point(&pdir, &dir2, 1) != 1)
		return (dprintf(1, "CAMERA DIRECTION ERROR ¯\\_(ツ)_/¯\n"));

	// Parse fov
	if (isnan(fov = (double)ft_atof(tokens[3])))
		return(printf("BAD FOV ...\n"));
	if (!check_fov((int)fov))
		return (printf("FOV ERROR ...\n"));

	normalize(&dir1, dir2);
	init_camera(cam, loc, dir1, fov);
	return (1);
}

int		check_res (char **tokens, t_rt *rt)
{
	double X;
	double Y;
	int i;

	i = 0;
	if (rt->has_res)
		return (dprintf(1, "RESOLUION IS ALREADY SET! \\_(-_-)_/\n"));
	if (check_tokens(&tokens, 3, "ELEMENT", "RESOLUTION") != 1)
		return (dprintf(1, "RESOLUTION ERROR ¯\\_(ツ)_/¯\n"));
	if (isnan(X = (double)ft_atoi(tokens[1])) || (int)X <= 0)
		return (dprintf(1, "BAD WINDOW WIDTH >_<\n"));
	if (isnan(Y = (double)ft_atoi(tokens[2])) || (int)Y <= 0)
		return (dprintf(1, "BAD WINDOW HEIGHT >_<\n"));
	rt->res.X = (int)X;
	rt->res.Y = (int)Y;
	rt->has_res = 1;
	return (1);
}

int		check_rgb(char ***tokens, t_color *color)
{
	int i;
	double r;
	double g;
	double b;

	i = 0;
	if (check_tokens(tokens, 3, "COLOR", "RGB") != 1)
		return (dprintf(1, "RGB ERROR... (=____=)\n"));
	if (isnan(r = (double)ft_atof((*tokens)[0])) || (int)r < 0 || (int)r > 255)
		return (dprintf(1, "BAD RED COLOR!\n"));
	if (isnan(g = (double)ft_atof((*tokens)[1])) || (int)g < 0 || (int)g > 255)
		return (dprintf(1, "BAD GREEN COLOR!\n"));
	if (isnan(b = (double)ft_atof((*tokens)[2])) || (int)b < 0 || (int)b > 255)
		return (dprintf(1, "BAD BLUE COLOR!\n"));
	if (r - (double)((int)r) > 0.0 || g - (double)((int)g) > 0.0 || \
		b - (double)((int)b) > 0.0)
		return (dprintf(1, "COLOR MUST BE AN INT! OH BOI\n"));
	set_color(color, (int)r, (int)g, (int)b);
	free_arr((void**)*tokens, 3);
	return (1);
}


int		check_lamb(char **tokens, t_rt *rt)
{
	double lum;
	char **rgb;
	int i;
	t_color	color;

	i = 0;
	if (rt->has_lamb)
		return(dprintf(1, "AMBIENCE IS ALREADY SET!\n"));
	if (check_tokens(&tokens, 3, "ELEMENT", "AMBIENCE") != 1)
		return (dprintf(1, "AMBIENCE ERROR... \n"));
	if (isnan(lum = (double)ft_atof(tokens[1])))
		return (dprintf(1, "BAD LUMINANCE!\n"));
	if (lum < 0 || lum > 1)
		return (dprintf(1, "LUMINANCE OUT OF RANGE [0,1]\n"));
	if (!(rgb = ft_strsplit(tokens[2], ",")))
		return (-1);
	if (check_rgb(&rgb, &color) != 1)
		return (dprintf(1, "BAD AMBIENT COLOR!\n"));
	set_lamb(&rt->lamb, lum, &color);
	rt->has_lamb = 1;
	return (1);
}


int		check_lsrc(char **tokens, t_lsrc *lsrc)
{
	double lum;
	char **rgb;
	char **ploc;

	if (check_tokens(&tokens, 4, "ELEMENT", "LIGHT SOURCE") != 1)
		return (dprintf(1, "LIGHT ERROR... \n"));

	// Check lum
	if (isnan(lum = (double)ft_atof(tokens[2])))
		return (dprintf(1, "BAD LUMINANCE!\n"));
	if (lum < 0 || lum > 1)
		return (dprintf(1, "LUMINANCE OUT OF RANGE [0,1]\n"));		
	lsrc->lum = lum;

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[3], ",")))
		return (-1);
	if (check_rgb(&rgb, &lsrc->col) != 1)
		return (dprintf(1, "BAD LIGHT COLOR!\n"));
	
	// Check location
	if (!(ploc = ft_strsplit(tokens[1], ",")))
		return (-1);
	if (check_point(&ploc, &lsrc->loc, 0) != 1)
		return (dprintf(1, "LIGHT LOCATION ERROR ¯\\_(ツ)_/¯\n"));
	// set_lsrc(lsrc, lum, color, p);
	return (1);
}

int			check_posdir(char **tokens, t_p3d *l, t_p3d *d, char *type)
{
	char **ploc;
	char **pdir;
	// TODO: char **rgb;

	// Parse location
	if (!(ploc = ft_strsplit(tokens[1], ",")))
		return (-1);
	if (check_point(&ploc, l, 0) != 1)
		return (dprintf(1, "%s LOCATION ERROR ¯\\_(ツ)_/¯\n", type));

	// Parse direction
	if (d != NULL)
	{
		if (!(pdir = ft_strsplit(tokens[2], ",")))
			return (-1);
		if (check_point(&pdir, d, 1) != 1)
			return (dprintf(1, "%s DIRECTION ERROR ¯\\_(ツ)_/¯\n", type));
	}
	return (1);
}

int			check_pl(char **tokens, t_rt *rt)
{
	t_pl	pl;
	t_p3d	tmp;
	char	**rgb;
	t_pl	*out;
	
	if (check_posdir(tokens, &pl.p, &tmp, "PLANE") != 1)
		return (dprintf(1, "PLANE ERROR...\n"));
	if (!(rgb = ft_strsplit(tokens[3], ",")))
		return (-1);
	if (check_rgb(&rgb, &pl.color) != 1)
		return (dprintf(1, "PLANE COLOR ERROR...\n"));

	normalize(&pl.dir, tmp);
	if (!(out = ft_memdup(&pl, sizeof(t_pl))))
		return (-1);
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, PL, 4);
	return (1);
}

int		check_sp(char **tokens, t_rt *rt)
{
	t_sp sp;
	char	**rgb;
	char	**ploc;

	// Check diameter
	if (isnan(sp.d = (double)ft_atof(tokens[2])) || sp.d <= 0)
		return (dprintf(1, "SPHERE DIAMETER MUST BE POSITIVE!\n"));

	// Check center
	if (!(ploc = ft_strsplit(tokens[1], ",")))
		return (-1);
	if (check_point(&ploc, &sp.c, 0) != 1)
		return (dprintf(1, "SPHERE CENTER ERROR\n"));

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[3], ",")))
		return (-1);
	if (check_rgb(&rgb, &sp.color) != 1)
		return(dprintf(1, "SPHERE COLOR ERROR\n"));

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

	// Check size
	if (isnan(size = (double)ft_atof(tokens[3])) || size <= 0)
		return (dprintf(1, "SQUARE SIZE MUST BE POSITIVE!\n"));
	sq.size = size;

	// Check center & normal
	if (check_posdir(tokens, &sq.c, &sq.dir, "SQUARE") != 1)
		return (printf("SQUARE ERROR...\n"));

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[4], ",")))
		return (-1);
	if (check_rgb(&rgb, &sq.color) != 1)
		return(dprintf(1, "SQUARE COLOR ERROR\n"));

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

	// Check points
	if (check_posdir(tokens, &tr.A, NULL, "TRIANGLE") != 1 || \
		check_posdir(tokens + 1, &tr.B, NULL, "TRIANGLE") != 1 || \
		check_posdir(tokens + 2, &tr.C, NULL, "TRIANGLE") != 1)
		return (dprintf(1, "TRIANGLE POINT ERROR...\n"));

	// Check rgb
	if (!(arr = ft_strsplit(tokens[4], ",")))
		return (-1);
	if (check_rgb(&arr, &tr.color) != 1)
		return (dprintf(1, "TRIANGLE COLOR ERROR...\n"));

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

	// Check diameter
	if (isnan(cy.d = (double)ft_atof(tokens[3])) || cy.d <= 0)
		return (dprintf(1, "CYLINDER DIAMETER MUST BE POSITIVE!\n"));	

	// Check height
	if (isnan(cy.h = (double)ft_atof(tokens[4])) || cy.h <= 0)
		return (dprintf(1, "CYLINDER HEIGHT MUST BE POSITIVE!\n"));

	// Check rgb
	if (!(rgb = ft_strsplit(tokens[5], ",")))
		return (-1);
	if (check_rgb(&rgb, &cy.color) != 1)
		return (dprintf(1, "CYLINDER COLOR ERROR...\n"));

	// Check posdir
	if (check_posdir(tokens, &cy.c, &cy.dir, "CYLINDER") != 1)
		return (dprintf(1, "CYLINDER POINT ERROR...\n"));

	// Copy cylinder to array
	if (!(out = ft_memdup(&cy, sizeof(t_cy))))
		return (-1);
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, CY, 4);
	return (1);
}

