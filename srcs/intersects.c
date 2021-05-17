#include "minirt.h"

double	plane_intersect(t_pl *pl, t_ray r)
{	
	t_p3d	ray_to_p;
	double	root;
	double	ray_dot_plane;
	double	ray_to_p_dot_plane;

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

t_p2d	infinite_cylinder_intersect(t_cy *cy, t_ray r)
{
	double	abc[3];
	double	disc;
	t_p3d	oc;
	t_p2d	roots;

	roots.x = NAN;
	roots.y = NAN;
	normalize(&cy->dir, cy->dir);
	p_sub(&oc, r.loc, cy->c);
	abc[0] = dot(r.dir, r.dir) - pow(dot(r.dir, cy->dir), 2);
	abc[1] = 2 * (dot(r.dir, oc) - (dot(r.dir, cy->dir)) * dot(oc, cy->dir));
	abc[2] = dot(oc, oc) - pow(dot(oc, cy->dir), 2) - pow(cy->d / 2, 2);
	disc = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (roots);
	roots.x = -abc[1] + sqrt(disc);
	roots.y = -abc[1] - sqrt(disc);
	return (roots);
}

double	finite_cylinder_intersect(t_cy *cy, t_ray r, t_p2d roots)
{
	t_p3d	phits[2];
	double	maxlen;

	maxlen = cy->h / 2;
	if (roots.x <= 0 && roots.y <= 0)
		return (NAN);
	if (roots.x <= 0)
		return (roots.y);
	scalmult(&phits[0], r.dir, roots.x);
	p_add(&phits[0], phits[0], r.loc);
	scalmult(&phits[1], r.dir, roots.y);
	p_add(&phits[1], phits[1], r.loc);
	if (roots.x < roots.y && roots.x > 0)
		if (fabs(dot(phits[0], cy->dir)) < maxlen)
			return (roots.x);
	if (roots.y < roots.x && roots.y > 0)
		if (fabs(dot(phits[1], cy->dir)) < maxlen)
			return (roots.y);
	return (NAN);
}

double	square_intersect(t_sq *sq, t_ray r)
{
	t_p3d	e1;
	t_p3d	e2;
	t_p3d	p;
	double	root;
	double	projs[2];

	root = plane_intersect(&(t_pl){sq->dir, sq->c, sq->color}, r);
	if (isnan(root))
		return (NAN);
	cross(&e1, sq->dir, (t_p3d){1, 0, 0});
	cross(&e2, sq->dir, e1);
	if (is_not_zero(e1))
		normalize(&e1, e1);
	if (is_not_zero(e2))
		normalize(&e2, e2);
	scalmult(&p, r.dir, root);
	p_add(&p, r.loc, p);
	projs[0] = dot(p, e1);
	projs[1] = dot(p, e2);
	if (fabs(projs[0]) <= (sq->size / 2) && fabs(projs[1]) <= (sq->size / 2))
		return (root);
	return (NAN);
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
	d = pow(prod, 2) - 4 * (dot(ray_to_c, ray_to_c) - \
	pow((double)(sp->d / 2), 2));
	a = dot(r.dir, r.dir);
	if (d < 0)
		return ((double)NAN);
	root = get_min_pos_root(d, a, prod);
	if (isnan((double)root))
		return ((double)NAN);
	return (root);
}

double	triangle_intersect(t_tr *tr, t_ray r)
{
	t_p3d	e[2];
	t_p3d	ptq[3];
	double	det;
	double	inv_det;
	double	uv[2];

	p_sub(&e[0], tr->B, tr->A);
	p_sub(&e[1], tr->C, tr->A);
	cross(&ptq[0], r.dir, e[1]);
	det = dot(e[0], ptq[0]);
	if (-1e-8 <= det && det <= 1e-8)
		return (NAN);
	inv_det = pow(det, -1);
	p_sub(&ptq[1], r.loc, tr->A);
	uv[0] = dot(ptq[1], ptq[0]) * inv_det;
	if (uv[0] < 0 || uv[0] > 1)
		return (NAN);
	cross(&ptq[2], ptq[1], e[0]);
	uv[1] = dot(r.dir, ptq[2]) * inv_det;
	if (uv[1] < 0 || uv[0] + uv[1] > 1)
		return (NAN);
	return (dot(e[1], ptq[2]) * inv_det);
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
