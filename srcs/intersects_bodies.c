#include "minirt.h"

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
