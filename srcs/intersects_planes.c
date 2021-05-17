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
