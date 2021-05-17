#include "minirt.h"

t_p3d	p_mult(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, v.x * u.x, v.y * u.y, v.z * u.z);
	return (*c);
}

t_p3d	cross(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, \
	v.z * u.y - v.y * u.z, \
	v.x * u.z - v.z * u.x, \
	v.y * u.x - v.x * u.y);
	return (*c);
}

double	dot(t_p3d v, t_p3d u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}
