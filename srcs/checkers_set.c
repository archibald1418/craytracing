#include "minirt.h"

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
