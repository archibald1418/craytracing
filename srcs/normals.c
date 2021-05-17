#include "minirt.h"

void	calc_point_normal(t_v3d *orient, t_shape shape, t_ray ray)
{
	if (ft_strcmp(shape.label, SP) == 0)
		return (get_sp_normal(orient, (t_sp *)shape.shape, ray));
	if (ft_strcmp(shape.label, SQ) == 0)
		return (get_sq_normal(orient, (t_sq *)shape.shape, ray));
	if (ft_strcmp(shape.label, PL) == 0)
		return (get_pl_normal(orient, (t_pl *)shape.shape, ray));
	if (ft_strcmp(shape.label, CY) == 0)
		return (get_cy_normal(orient, (t_cy *)shape.shape, ray));
	if (ft_strcmp(shape.label, TR) == 0)
		return (get_tr_normal(orient, (t_tr *)shape.shape, ray));
}
