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

int	check_fov(int fov)
{
	if (!(0 < fov && fov <= 180))
		return (handle_errors("FOV NOT IN RANGE [0, 180]\n"));
	return (1);
}
