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

double	infinite_cylinder_intersect(t_cy *cy, t_ray r)
{
	double a;
	double b;
	double c;
	double disc;
	t_p3d oc;
	double root;

	normalize(&cy->dir, cy->dir);
	p_sub(&oc, r.loc, cy->c);
	a = dot(r.dir, r.dir) - pow(dot(r.dir, cy->dir), 2);
	b = 2 * (dot(r.dir, oc) - (dot(r.dir, cy->dir)) * dot(oc, cy->dir));
	c = dot(oc, oc) - pow(dot(oc, cy->dir), 2) - pow(cy->d/2, 2);
	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (NAN);
	if (isnan(root = get_min_pos_root(disc, a, b)))
		return (NAN);
	return (root);
}

double	finite_cylinder_intersect(t_cy *cy, t_ray r, double root)
{
	double proj;
	t_p3d phit;
	double diff;
	double halfh;
	
    scalmult(&phit, r.dir, root);
    p_add(&phit, phit, r.loc);

	halfh = cy->h / 2;
	proj = dot(phit, cy->dir);
	diff = fabs(halfh - proj);
	if (diff > halfh)
		return (NAN);
	return (root);
}

double	square_intersect(t_sq *sq, t_ray r)
{
	// const double magn = sqrt(2)* sq->size;
	t_p3d e1;
	t_p3d e2;
	t_p3d p;
	double root;
	double proja;
	double projb;
	
	// t_p3d vert[4];
	// t_p3d crss[4];
	// double dots[4];

	root = plane_intersect(&(t_pl){sq->dir, sq->c, sq->color}, r);
	if (isnan(root))
		return (NAN);

	// Find square's basis
	cross(&e1, sq->dir, (t_p3d){1,0,0});
	cross(&e2, sq->dir, e1);
	normalize(&e1, e1);
	normalize(&e2, e2);

	// Find point on ray
	scalmult(&p, r.dir, root);
	p_add(&p, r.loc, p);

	// Get projections of point on axes
	proja = dot(p, e1);
	projb = dot(p, e2);
	if (fabs(proja) <= (sq->size / 2) && fabs(projb) <= (sq->size / 2))
		return (root);
	return (NAN);
	

	// scalmult(&vert[0], e1, magn);
	// p_add(&vert[0], vert[0], sq->c);

	// scalmult(&vert[1], e1, -magn);
	// p_add(&vert[1], vert[1], sq->c);

	// scalmult(&vert[2], e2, magn);
	// p_add(&vert[2], vert[2], sq->c);
	
	// scalmult(&vert[3], e2, -magn);
	// p_add(&vert[3], vert[3], sq->c);


	// TODO: two square axes dot plane hit -> the square hit



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
	double root;

	root = NAN;
    if (ft_strcmp(shape.label, SP) == 0)
        return((double)sphere_intersect((t_sp *)shape.shape, ray));
	if (ft_strcmp(shape.label, SQ) == 0)
        return((double)square_intersect((t_sq *)shape.shape, ray));
    if (ft_strcmp(shape.label, PL) == 0)
        return((double)plane_intersect((t_pl *)shape.shape, ray));
    if (ft_strcmp(shape.label, CY) == 0)
	{
		root = infinite_cylinder_intersect((t_cy *)shape.shape, ray);
		if (!(isnan(root)))
			return (finite_cylinder_intersect((t_cy *)shape.shape, ray, root));
	}
    if (ft_strcmp(shape.label, TR) == 0)
        return((double)triangle_intersect((t_tr *)shape.shape, ray));
    return ((double)NAN);
}