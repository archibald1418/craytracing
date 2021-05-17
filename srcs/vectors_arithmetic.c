#include "minirt.h"

t_p3d	p_add(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, \
	v.x + u.x, \
	v.y + u.y, \
	v.z + u.z);
	return (*c);
}

t_p3d	p_sub(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, \
	v.x - u.x, \
	v.y - u.y, \
	v.z - u.z);
	return (*c);
}

t_p3d	scaldiv(t_p3d *c, t_p3d v, double s)
{
	if (s == 0)
	{
		handle_errors("DIVISION BY ZERO ERROR!\n");
		return ((t_p3d){0, 0, 0});
	}
	init_p3d(c, v.x * pow(s, -1), v.y * pow(s, -1), v.z * pow(s, -1));
	return (*c);
}

t_p3d	scalmult(t_p3d *c, t_p3d v, double s)
{
	init_p3d(c, v.x * s, v.y * s, v.z * s);
	return (*c);
}
