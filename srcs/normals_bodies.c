#include "minirt.h"

void	get_sp_normal(t_v3d *orient, t_sp *sp, t_ray ray)
{
	(void)ray;
	p_sub(&orient->dir, orient->loc, sp->c);
	normalize(&orient->dir, orient->dir);
}

void	get_cy_normal(t_v3d *orient, t_cy *cy, t_ray ray)
{
	t_p3d	tangent;
	t_p3d	pc;

	(void)ray;
	p_sub(&pc, orient->loc, cy->c);
	cross(&tangent, cy->dir, pc);
	cross(&orient->dir, tangent, cy->dir);
	normalize(&orient->dir, orient->dir);
}
