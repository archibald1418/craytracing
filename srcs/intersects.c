#include "minirt.h"

t_color	get_shape_color(t_shape shape)
{
	if (ft_strncmp(shape.label, SP, ft_strlen(SP)) == 0)
		return (((t_sp *)shape.shape)->color);
	if (ft_strncmp(shape.label, SQ, ft_strlen(SQ)) == 0)
		return (((t_sq *)shape.shape)->color);
	if (ft_strncmp(shape.label, PL, ft_strlen(PL)) == 0)
		return (((t_pl *)shape.shape)->color);
	if (ft_strncmp(shape.label, CY, ft_strlen(CY)) == 0)
		return (((t_cy *)shape.shape)->color);
	if (ft_strncmp(shape.label, TR, ft_strlen(TR)) == 0)
		return (((t_tr *)shape.shape)->color);
	return ((t_color){0, 0, 0});
}

double	intersect_shape(t_shape shape, t_ray ray)
{
	t_p2d	cylinder_roots;

	cylinder_roots.x = NAN;
	cylinder_roots.y = NAN;
	if (ft_strcmp(shape.label, SP) == 0)
		return ((double)sphere_intersect((t_sp *)shape.shape, ray));
	if (ft_strcmp(shape.label, SQ) == 0)
		return ((double)square_intersect((t_sq *)shape.shape, ray));
	if (ft_strcmp(shape.label, PL) == 0)
		return ((double)plane_intersect((t_pl *)shape.shape, ray));
	if (ft_strcmp(shape.label, CY) == 0)
	{
		cylinder_roots = infinite_cylinder_intersect((t_cy *)shape.shape, ray);
		if (!(isnan(cylinder_roots.x) && !(isnan(cylinder_roots.y))))
			return (finite_cylinder_intersect((t_cy *)shape.shape, \
			ray, \
			cylinder_roots));
	}
	if (ft_strcmp(shape.label, TR) == 0)
		return ((double)triangle_intersect((t_tr *)shape.shape, ray));
	return ((double)NAN);
}
