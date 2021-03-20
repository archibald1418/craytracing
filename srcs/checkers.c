#include "minirt.h"

int		check_rt(t_rt *rt)
{
	return (rt->res || rt->lamb || rt->shapes || rt->lsrcs || rt->cams);
}

int		check_res (char **tokens, t_rt *rt)
{
	double X;
	double Y;
	int i;

	i = 0;
	if (rt->res)
		return (dprintf(1, "RESOLUION IS ALREADY SET!\n"));
	while (tokens[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY ELEMENTS IN RESOLUTION"));
	if (i < 3)
		return (dprintf(1, "TOO FEW ELEMENTS IN RESOLUTION"));
	if (isnan(X = (double)ft_atof(tokens[1])) || (int)X <= 0)
		return (dprintf(1, "BAD WINDOW WIDTH"));
	if (isnan(Y = (double)ft_atof(tokens[2])) || (int)Y <= 0)
		return (dprintf(1, "BAD WINDOW HEIGHT"));
	// TODO: silently adjust resolution to max_screen_size
	rt->res = &(t_res){(int)X, (int)Y};
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
		return (dprintf(1, "TOO FEW COLORS IN RGB!"));
	if (isnan(r = (double)ft_atof((*tokens)[0])) || (int)r < 0 || (int)r > 255)
		return (dprintf(1, "BAD RED COLOR!"));
	if (isnan(g = (double)ft_atof((*tokens)[1])) || (int)g < 0 || (int)g > 255)
		return (dprintf(1, "BAD GREEN COLOR!"));
	if (isnan(b = (double)ft_atof((*tokens)[2])) || (int)b < 0 || (int)b > 255)
		return (dprintf(1, "BAD BLUE COLOR!"));
	if (r - (double)((int)r) > 0.0 || g - (double)((int)g) > 0.0 || \
		b - (double)((int)b) > 0.0)
		return (dprintf(1, "COLOR MUST BE AN INT!"));
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
	if (rt->lamb)
		return(dprintf(1, "AMBIENCE IS ALREADY SET!"));
	while (tokens[i] != NULL)
		if (++i > 3)
			return (dprintf(1, "TOO MANY ELEMENTS IN AMBIENCE!"));
	if (i < 3)
		return (dprintf(1, "TOO FEW ELEMENTS IN AMBEINCE!"));
	if (isnan(lum = (double)ft_atof(tokens[1])))
		return (dprintf(1, "BAD LUMINANCE!"));
	if (lum < 0 || lum > 1)
		return (dprintf(1, "LUMINANCE OUT OF RANGE [0,1]"));
	if (!(rgb = ft_strsplit(tokens[2], ",")))
		return (-1);
	if (check_rgb(&rgb, &color) != 1)
		return (dprintf(1, "BAD COLOR!"));
	set_lamb(&lamb, lum, &color);
	return (1);
}
