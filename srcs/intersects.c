#include "minirt.h"

double	plane_intersect(t_pl *pl, t_ray r)
{	
	t_p3d ray_to_p;
	double root;
	double ray_dot_plane;
	double ray_to_p_dot_plane;

	p_sub(&ray_to_p, r.loc, pl->p);
	ray_dot_plane = dot(r.dir, pl->dir);
	if (-EPSILON <= ray_dot_plane && ray_dot_plane <= EPSILON)
		return (NAN);
	ray_to_p_dot_plane = dot(ray_to_p, pl->dir);
	root = -ray_to_p_dot_plane / ray_dot_plane;
	if (root <= 0)
		return (NAN);
	return (root);
}

double	sphere_intersect(t_sp *sp, t_ray r)
{
	t_p3d	ray_to_c;
	double	prod;
	double	d;
	double	a;
	double	root;

	p_sub(&ray_to_c, r.loc, sp->c);
	prod = 2 * dot(r.dir, ray_to_c);
	d = pow(prod, 2) - 4 * (dot(ray_to_c, ray_to_c) - pow((double)(sp->d/2), 2));
	a = dot(r.dir, r.dir);
	if (d < 0)
		return ((double)NAN);
	if (isnan((double)(root = get_min_pos_root(d, a, prod))))
		return ((double)NAN);
	// scalmult(ipoint, r->dir, root);
	// p_add(ipoint, ipoint, r->loc);
	return (root);
}

double  intersect_shape(t_shape shape, t_ray ray)
{
    if (ft_strcmp(shape.label, SP) == 0)
        return((double)sphere_intersect((t_sp *)shape.shape, ray));

    //TODO: 
	// if (ft_strcmp(shape.label, SQ))
    //     return((double)sphere_intersect((t_sq *)shape.shape, ray));
    // if (ft_strcmp(shape.label, PL))
    //     return((double)sphere_intersect((t_pl *)shape.shape, ray));
    // if (ft_strcmp(shape.label, CY))
    //     return((double)sphere_intersect((t_cy *)shape.shape, ray));
    // if (ft_strcmp(shape.label, TR))
    //     return((double)sphere_intersect((t_tr *)shape.shape, ray));
    return ((double)NAN);
}