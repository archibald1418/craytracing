#include "minirt.h"

void    get_sp_normal(t_v3d *orient, t_sp *sp, t_ray ray)
{
    (void)ray;
    p_sub(&orient->dir, orient->loc, sp->c);
	normalize(&orient->dir, orient->dir);
	// TODO: try reversing normals again (after normalizing)
}

void	get_pl_normal(t_v3d *orient, t_pl *pl, t_ray ray)
{
	double ray_to_plane;
    init_p3d(&orient->dir, pl->dir.x, pl->dir.y, pl->dir.z);
    normalize(&orient->dir, orient->dir);
	ray_to_plane = dot(ray.dir, pl->dir);
    if (ray_to_plane >= 0)
        scalmult(&orient->dir, orient->dir, -1);
}

void    calc_point_normal(t_v3d *orient, t_shape shape, t_ray ray)
{
	(void)ray;
	// t_p3d c_to_ray;
	// double light_angle;
     if (ft_strcmp(shape.label, SP) == 0)
        return (get_sp_normal(orient, (t_sp *)shape.shape, ray));

    //TODO: 
	// if (ft_strcmp(shape.label, SQ))
    //     return(get_sp_normal((t_sq *)shape.shape, ray));
    if (ft_strcmp(shape.label, PL) == 0)
        return(get_pl_normal(orient, (t_pl *)shape.shape, ray));
    // if (ft_strcmp(shape.label, CY))
    //     return(get_sp_normal((t_cy *)shape.shape, ray));
    // if (ft_strcmp(shape.label, TR))
    //     return(get_sp_normal((t_tr *)shape.shape, ray));
	// p_sub(&c_to_ray, )
}