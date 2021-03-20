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
		return (printf("RESOLUION IS ALREADY SET!\n"));
	while (tokens[i] != NULL)
		if (i > 2)
			return (printf("TOO MANY ELEMENTS IN RESOLUTION"));
	if (i < 2)
		return (printf("TOO FEW ELEMENTS IN RESOLUTION"));
	if (isnan(X = (double)ft_atof((*tokens)[1])) || (int)X <= 0)
		return (printf("BAD WINDOW WIDTH"));
	if (isnan(Y = (double)ft_atof((*tokens)[2])) || (int)Y <= 0)
		return (printf("BAD WINDOW HEIGHT"));
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
		if (i++ > 2)
			return (printf("TOO FEW COLORS IN RGB!"));
	if (i < 2)
		return (printf("TOO MANY COLORS IN RGB!"));
	if (isnan(r = (double)ft_atof((*tokens)[0])) || (int)r < 0 || (int)r > 255)
		return (printf("BAD RED COLOR!"));
	if (isnan(g = (double)ft_atof((*tokens)[1])) || (int)g < 0 || (int)g > 255)
		return (printf("BAD RED COLOR!"));
	if (isnan(b = (double)ft_atof((*tokens)[2])) || (int)b < 0 || (int)b > 255)
		return (printf("BAD RED COLOR!"));
	if (r - (double)((int)r) > 0.0 || g - (double)((int)g) > 0.0 || \
		b - (double)((int)b) > 0.0)
		return (printf("COLOR MUST BE AN INT!"));
	set_color(color, (int)r, (int)g, (int)b);
	return (1);
}


int		check_amb(char **tokens, t_rt *rt)
{
	double lum;
	char **rgb;
	int i;
	int tmp;
	t_color	color;

	i = 0;
	if (rt->lamb)
		return(printf("AMBIENCE IS ALREADY SET!"));
	while (tokens[i] != NULL)
		if (i++ > 2)
			return (printf("TOO MANY ELEMENTS IN AMBIENCE!"));
	if (i < 2)
		return (printf("TOO FEW ELEMENTS IN AMBEINCE!"));
	if (isnan(lum = (double)ft_atof((*tokens)[1])) || (int)lum < 0)
		return (printf("BAD LUMINANCE!"));
	if (!(rgb = ft_strsplit(tokens[2], ",")))
		return (-1);
	if (check_rgb(&tokens, &color) != 1)
		return (printf("BAD COLOR!"));
	rt->lamb->col = color;
	rt->lamb->lum = lum;
	return (1);
}
