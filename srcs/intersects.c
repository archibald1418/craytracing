#include "minirt.h"

double	plane_intersect(t_pl *pl, t_ray r)
{	
	t_p3d ray_to_p;
	double root;
	double ray_dot_plane;
	double ray_to_p_dot_plane;

	p_sub(&ray_to_p, r.loc, pl->p);
	ray_dot_plane = dot(r.dir, pl->dir);
	if (-1e-8 <= ray_dot_plane && ray_dot_plane <= 1e-8)
		return (NAN);
	ray_to_p_dot_plane = dot(ray_to_p, pl->dir);
	root = -ray_to_p_dot_plane * pow(ray_dot_plane, -1);
	if (root < 0)
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

double	triangle_intersect(t_tr *tr, t_ray r)
{
	t_p3d e1;
	t_p3d e2;
	t_p3d pvec;
	t_p3d tvec;
	t_p3d qvec;
	double det;
	double inv_det;
	double u;
	double v;


	p_sub(&e1, tr->B, tr->A);
	p_sub(&e2, tr->C, tr->A);
	// normalize(&e1, e1);
	// normalize(&e2, e2);
	cross(&pvec, r.dir, e2);
	// normalize(&pvec, pvec);
	det = dot(e1, pvec);

	// Is parallel
	if (-1e-8 <= det && det <= 1e-8)
		return (NAN);

	inv_det = pow(det, -1);
	p_sub(&tvec, r.loc, tr->A);
	// normalize(&tvec, tvec);
	u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1)
		return (NAN);

	cross(&qvec, tvec, e1);
	// normalize(&qvec, qvec);
	v = dot(r.dir, qvec) * inv_det;
	if (v < 0 || u + v > 1)
		return (NAN);
	return (dot(e2, qvec) * inv_det);
}

double  intersect_shape(t_shape shape, t_ray ray)
{
    if (ft_strcmp(shape.label, SP) == 0)
        return((double)sphere_intersect((t_sp *)shape.shape, ray));

    //TODO: 
	// if (ft_strcmp(shape.label, SQ))
    //     return((double)sphere_intersect((t_sq *)shape.shape, ray));
    if (ft_strcmp(shape.label, PL) == 0)
        return((double)plane_intersect((t_pl *)shape.shape, ray));
    // if (ft_strcmp(shape.label, CY))
    //     return((double)sphere_intersect((t_cy *)shape.shape, ray));
    if (ft_strcmp(shape.label, TR) == 0)
        return((double)triangle_intersect((t_tr *)shape.shape, ray));
    return ((double)NAN);
}