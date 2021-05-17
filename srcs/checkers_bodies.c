#include "minirt.h"

int	check_sp(char **tokens, t_rt *rt)
{
	t_sp	sp;
	char	**rgb;
	char	**ploc;

	if (check_tokens(&tokens, 4, "ELEMENT", "SP") != 1)
		return (handle_errors("SPHERE ERROR... \n"));
	sp.d = (double)ft_atof(tokens[2]);
	if (isnan(sp.d) || sp.d <= 0)
		return (handle_errors("SPHERE DIAMETER MUST BE POSITIVE!\n"));
	ploc = ft_strsplit(tokens[1], ",");
	if (!(ploc))
		return (handle_errors("SPHERE LOCATION ERROR...\n"));
	if (check_point(&ploc, &sp.c, 0) != 1)
		return (handle_errors("SPHERE CENTER ERROR\n"));
	rgb = ft_strsplit(tokens[3], ",");
	if (!(rgb))
		return (handle_errors("Malloc error...\n"));
	if (check_rgb(&rgb, &sp.color) != 1)
		return (handle_errors("SPHERE COLOR ERROR\n"));
	rt->shapes.shapes[rt->shapes.top].shape = ft_memdup(&sp, sizeof(t_sp));
	if (!(rt->shapes.shapes[rt->shapes.top].shape))
		return (handle_errors("Malloc error...\n"));
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, SP, 4);
	return (1);
}

int	check_cy(char **tokens, t_rt *rt)
{
	t_cy	cy;
	char	**rgb;
	t_cy	*out;

	if (check_tokens(&tokens, 6, "ELEMENT", "CYLINDER") != 1)
		return (handle_errors("PLANE CYLINDER... \n"));
	cy.d = (double)ft_atof(tokens[3]);
	if (isnan(cy.d) || cy.d <= 0)
		return (handle_errors("CYLINDER DIAMETER MUST BE POSITIVE!\n"));
	cy.h = (double)ft_atof(tokens[4]);
	if (isnan(cy.h) || cy.h <= 0)
		return (handle_errors("CYLINDER HEIGHT MUST BE POSITIVE!\n"));
	rgb = ft_strsplit(tokens[5], ",");
	if (!(rgb))
		return (handle_errors("Malloc error...\n"));
	if (check_rgb(&rgb, &cy.color) != 1)
		return (handle_errors("CYLINDER COLOR ERROR...\n"));
	if (parse_posdir(tokens, &cy.c, &cy.dir, "CYLINDER") != 1)
		return (handle_errors("CYLINDER POINT ERROR...\n"));
	out = ft_memdup(&cy, sizeof(t_cy));
	if (!(out))
		return (handle_errors("Malloc error...\n"));
	rt->shapes.shapes[rt->shapes.top].shape = out;
	ft_strlcpy(rt->shapes.shapes[rt->shapes.top].label, CY, 4);
	return (1);
}
