#include "minirt.h"

int		check_fov(int fov)
{
	if (!(0 <= fov && fov <= 180))
		return (dprintf(1, "FOV NOT IN RANGE [0, 180]\n"));
	// TODO: check zero fov at raycasting stage
	return (1);
}

int		check_point(char ***tokens, t_p3d *p, int is_normal)
{
	int i;
	const char *msgs[] = {"POINT", "NORMAL"};
	double x;
	double y;
	double z;

	i = 0;
	while ((*tokens)[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY COORDS IN %s", msgs[is_normal]));
	if (i < 3)
		return (dprintf(1, "TOO FEW COORDS IN %s!\n", msgs[is_normal]));
	if (isnan(x = (double)ft_atof((*tokens)[0])))
		return (dprintf(1, "BAD X COORD IN %s!\n", msgs[is_normal]));
	if (isnan(y = (double)ft_atof((*tokens)[1])))
		return (dprintf(1, "BAD Y COORD IN %s!\n", msgs[is_normal]));
	if (isnan(z = (double)ft_atof((*tokens)[2])))
		return (dprintf(1, "BAD Z COORD IN %s!\n", msgs[is_normal]));
	if (is_normal)
		if (x == 0 && y == 0 && z == 0)
			return ("ZERO NORMAL ERROR...\n");
	init_p3d(p, x, y, z);
	return (1);
	//
}

int		check_cam (char **tokens, t_cam *cam)
{
	int i;
	t_p3d loc;
	t_p3d dir;
	double fov;
	char **ploc;
	char **pdir;

	i = 0;
	while (tokens[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY ELEMENTS IN CAMERA\n"));
	if (i < 3)
		return (dprintf(1, "TOO FEW ELEMENTS IN CAMERA\n"));

	// Parse location
	if (!(ploc = ft_strsplit(tokens[1], ",")))
		return (-1);
	if (check_point(ploc, &loc, 0) != 1)
		return (dprintf(1, "CAMERA LOCATION ERROR...\n"));

	// Parse direction
	if (!(pdir = ft_strsplit(tokens[2], ",")))
		return (-1);
	if (check_point(pdir, &dir, 1) != 1)
		return (dprintf(1, "CAMERA DIRECTION ERROR\n"));

	// Parse fov
	if (isnan(fov = (double)ft_atof(tokens[2])))
		return(printf("BAD FOV\n"));
	if (!check_fov((int)fov))
		return (printf("FOV ERROR\n"));

	init_camera(cam, loc, dir, fov);
	return (1);
	//TODO: camera setter should also add to a list...
	//TODO: tests

}

int		check_res (char **tokens, t_rt *rt)
{
	double X;
	double Y;
	int i;

	i = 0;
	if (rt->res.X != 0 && rt->res.Y != 0)
		return (dprintf(1, "RESOLUION IS ALREADY SET!\n"));
	while (tokens[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY ELEMENTS IN RESOLUTION\n"));
	if (i < 3)
		return (dprintf(1, "TOO FEW ELEMENTS IN RESOLUTION\n"));
	if (isnan(X = (double)ft_atoi(tokens[1])) || (int)X <= 0)
		return (dprintf(1, "BAD WINDOW WIDTH\n"));
	if (isnan(Y = (double)ft_atoi(tokens[2])) || (int)Y <= 0)
		return (dprintf(1, "BAD WINDOW HEIGHT\n"));
	rt->res.X = (int)X;
	rt->res.Y = (int)Y;
	return (1);
}

int		check_rgb(char ***tokens, t_color *color)
{
	int i;
	double r;
	double g;
	double b;

	i = 0;
	while ((*tokens)[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY COLORS IN RGB!"));
	if (i < 3)
		return (dprintf(1, "TOO FEW COLORS IN RGB!\n"));
	if (isnan(r = (double)ft_atof((*tokens)[0])) || (int)r < 0 || (int)r > 255)
		return (dprintf(1, "BAD RED COLOR!\n"));
	if (isnan(g = (double)ft_atof((*tokens)[1])) || (int)g < 0 || (int)g > 255)
		return (dprintf(1, "BAD GREEN COLOR!\n"));
	if (isnan(b = (double)ft_atof((*tokens)[2])) || (int)b < 0 || (int)b > 255)
		return (dprintf(1, "BAD BLUE COLOR!\n"));
	if (r - (double)((int)r) > 0.0 || g - (double)((int)g) > 0.0 || \
		b - (double)((int)b) > 0.0)
		return (dprintf(1, "COLOR MUST BE AN INT!\n"));
	set_color(color, (int)r, (int)g, (int)b);
	return (1);
}


int		check_lamb(char **tokens, t_rt *rt)
{
	double lum;
	char **rgb;
	int i;
	t_color	color;
	t_lamb	lamb;

	i = 0;
	if (rt->lamb.lum != 0)
		return(dprintf(1, "AMBIENCE IS ALREADY SET!\n"));
		// No brightness results in no render
	while (tokens[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY ELEMENTS IN AMBIENCE!\n"));
	if (i < 3)
		return (dprintf(1, "TOO FEW ELEMENTS IN AMBEINCE!\n"));
	if (isnan(lum = (double)ft_atof(tokens[1])))
		return (dprintf(1, "BAD LUMINANCE!\n"));
	if (lum < 0 || lum > 1)
		return (dprintf(1, "LUMINANCE OUT OF RANGE [0,1]\n"));
	if (!(rgb = ft_strsplit(tokens[2], ",")))
		return (-1);
	if (check_rgb(&rgb, &color) != 1)
		return (dprintf(1, "BAD AMBIENT COLOR!\n"));
	set_lamb(&rt->lamb, lum, &color);
	return (1);
}