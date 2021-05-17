#include "minirt.h"

t_p3d	init_p3d(t_p3d *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
	return (*p);
}

t_v3d	init_v3d(t_v3d *v, t_p3d loc, t_p3d dir)
{
	init_p3d(&v->loc, loc.x, loc.y, loc.z);
	init_p3d(&v->dir, dir.x, dir.y, dir.z);
	return (*v);
}

double	get_len(t_p3d v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

double	get_dist(t_p3d v, t_p3d u)
{
	return (sqrt(pow(v.x - u.x, 2) + pow(v.y - u.y, 2) + pow(v.z - u.z, 2)));
}

t_p3d	normalize(t_p3d *n, t_p3d v)
{
	double	len;

	len = get_len(v);
	if (len == 0)
	{
		handle_errors("ZERO VECTOR CAN'T BE NORMALIZED!\n");
		return ((t_p3d){0, 0, 0});
	}
	scaldiv(n, v, len);
	return (*n);
}
