#include "minirt.h"

int	check_sq(char **tokens, t_rt *rt)
{
	t_sq	sq;
	char	**rgb;
	double	size;
	t_sq	*out;

	if (check_tokens(&tokens, 5, "ELEMENT", "SQUARE") != 1)
		return (handle_errors("SQUARE ERROR... \n"));
	size = (double)ft_atof(tokens[3]);
	if (isnan(size) || size <= 0)
		return (handle_errors("SQUARE SIZE MUST BE POSITIVE!\n"));
	sq.size = size;
	if (parse_posdir(tokens, &sq.c, &sq.dir, "SQUARE") != 1)
		return (handle_errors("SQUARE ERROR...\n"));
	rgb = ft_strsplit(tokens[4], ",");
	if (!(rgb))
		return (handle_errors("Malloc error...\n"));
	if (check_rgb(&rgb, &sq.color) != 1)
		return (handle_errors("SQUARE COLOR ERROR\n"));
	out = ft_memdup(&sq, sizeof(t_sq));
	if (!(out))
		return (handle_errors("Malloc error...\n"));
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, SQ, 4);
	return (1);
}

int	check_tr(char **tokens, t_rt *rt)
{
	t_tr	tr;
	char	**arr;
	t_tr	*out;

	if (check_tokens(&tokens, 5, "ELEMENT", "TRIANGLE") != 1)
		return (handle_errors("TRIANGLE ERROR... \n"));
	if (parse_posdir(tokens, &tr.A, NULL, "TRIANGLE") != 1 || \
		parse_posdir(tokens + 1, &tr.B, NULL, "TRIANGLE") != 1 || \
		parse_posdir(tokens + 2, &tr.C, NULL, "TRIANGLE") != 1)
		return (handle_errors("TRIANGLE POINT ERROR...\n"));
	arr = ft_strsplit(tokens[4], ",");
	if (!(arr))
		return (handle_errors("Malloc error...\n"));
	if (check_rgb(&arr, &tr.color) != 1)
		return (handle_errors("TRIANGLE COLOR ERROR...\n"));
	out = ft_memdup(&tr, sizeof(t_tr));
	if (!(out))
		return (handle_errors("Malloc error...\n"));
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, TR, 4);
	return (1);
}

int	check_pl(char **tokens, t_rt *rt)
{
	t_pl	pl;
	t_p3d	tmp;
	char	**rgb;
	t_pl	*out;

	if (check_tokens(&tokens, 4, "ELEMENT", "PLANE") != 1)
		return (handle_errors("PLANE ERROR... \n"));
	if (parse_posdir(tokens, &pl.p, &tmp, "PLANE") != 1)
		return (handle_errors("PLANE ERROR...\n"));
	rgb = ft_strsplit(tokens[3], ",");
	if (!(rgb))
		return (handle_errors("Malloc error...\n"));
	if (check_rgb(&rgb, &pl.color) != 1)
		return (handle_errors("PLANE COLOR ERROR...\n"));
	normalize(&pl.dir, tmp);
	out = ft_memdup(&pl, sizeof(t_pl));
	if (!(out))
		return (handle_errors("Malloc error...\n"));
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, PL, 4);
	return (1);
}
