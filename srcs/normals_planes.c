#include "minirt.h"

void	get_pl_normal(t_v3d *orient, t_pl *pl, t_ray ray)
{
	double	ray_dot_plane;

	init_p3d(&orient->dir, pl->dir.x, pl->dir.y, pl->dir.z);
	normalize(&orient->dir, orient->dir);
	ray_dot_plane = dot(ray.dir, pl->dir);
	if (ray_dot_plane > 0)
		scalmult(&orient->dir, orient->dir, -1);
}

void	get_sq_normal(t_v3d *orient, t_sq *sq, t_ray ray)
{
	double	ray_dot_sq;

	init_p3d(&orient->dir, sq->dir.x, sq->dir.y, sq->dir.z);
	normalize(&orient->dir, orient->dir);
	ray_dot_sq = dot(ray.dir, sq->dir);
	if (ray_dot_sq > 0)
		scalmult(&orient->dir, orient->dir, -1);
}

void	get_tr_normal(t_v3d *orient, t_tr *tr, t_ray ray)
{
	double	ray_dot_tr;
	t_p3d	e1;
	t_p3d	e2;

	p_sub(&e1, tr->B, tr->A);
	p_sub(&e2, tr->C, tr->A);
	normalize(&e1, e1);
	normalize(&e2, e2);
	cross(&orient->dir, e1, e2);
	normalize(&orient->dir, orient->dir);
	ray_dot_tr = dot(ray.dir, orient->dir);
	if (ray_dot_tr >= 0)
		scalmult(&orient->dir, orient->dir, -1);
}
