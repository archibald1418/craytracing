#include "minirt.h"

void    get_sp_normal(t_v3d *orient, t_sp *sp, t_ray ray)
{
    (void)ray;
    p_sub(&orient->dir, orient->loc, sp->c);
	normalize(&orient->dir, orient->dir);
}

void	get_pl_normal(t_v3d *orient, t_pl *pl, t_ray ray)
{
	double ray_dot_plane;
    init_p3d(&orient->dir, pl->dir.x, pl->dir.y, pl->dir.z);
    normalize(&orient->dir, orient->dir);
	ray_dot_plane = dot(ray.dir, pl->dir);
    if (ray_dot_plane > 0)
        scalmult(&orient->dir, orient->dir, -1);
}

void    get_sq_normal(t_v3d *orient, t_sq *sq, t_ray ray)
{
    double ray_dot_sq;

    init_p3d(&orient->dir, sq->dir.x, sq->dir.y, sq->dir.z);
    normalize(&orient->dir, orient->dir);
    ray_dot_sq = dot(ray.dir, sq->dir);
    if (ray_dot_sq > 0)
        scalmult(&orient->dir, orient->dir, -1);
}

void    get_tr_normal(t_v3d *orient, t_tr *tr, t_ray ray)
{
    double ray_dot_tr;
    t_p3d e1;
    t_p3d e2;

	p_sub(&e1, tr->B, tr->A);
	p_sub(&e2, tr->C, tr->A);
    normalize(&e1, e1);
    normalize(&e2, e2);

    cross(&orient->dir, e1, e2);
    normalize(&orient->dir,   orient->dir);
    ray_dot_tr = dot(ray.dir, orient->dir);
    if (ray_dot_tr >= 0)
        scalmult(&orient->dir, orient->dir, -1);
}

void    get_cy_normal(t_v3d *orient, t_cy *cy, t_ray ray)
{
    t_p3d tangent;
    t_p3d pc;
    (void)ray;

    p_sub(&pc, orient->loc, cy->c);
    cross(&tangent, cy->dir, pc);
    cross(&orient->dir, tangent, cy->dir);
    normalize(&orient->dir, orient->dir);

    // // Find Normal
    // p_sub(&orient->dir, orient->loc, cy->c);
    // scalmult(&tmp, cy->dir, m);
    // p_sub(&orient->dir, orient->dir, tmp);
    // normalize(&orient->dir, orient->dir);
}


void    calc_point_normal(t_v3d *orient, t_shape shape, t_ray ray)
{
    if (ft_strcmp(shape.label, SP) == 0)
        return (get_sp_normal(orient, (t_sp *)shape.shape, ray));
	if (ft_strcmp(shape.label, SQ) == 0)
        return(get_sq_normal(orient, (t_sq *)shape.shape, ray));
    if (ft_strcmp(shape.label, PL) == 0)
        return(get_pl_normal(orient, (t_pl *)shape.shape, ray));
    if (ft_strcmp(shape.label, CY) == 0)
        return(get_cy_normal(orient, (t_cy *)shape.shape, ray));
    if (ft_strcmp(shape.label, TR) == 0)
        return(get_tr_normal(orient, (t_tr *)shape.shape, ray));
}