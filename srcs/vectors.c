#include "minirt.h"

/*
USEFUL FUNC:
math.fma(x, y, z) -> x*y + z
math.hypot (x, y) -> sqrt(x*x + y*y)
math.modf (x, &y) -> the fractional part of x and stores the integral part in y
math.frexp(x, &n) returns the mantissa of x and stores the exponent in n
math.fdim (x, y) -> abs(x - y)
math.copysign (-8, 154) -> 8 (magnitude of x + sign of y)
*/

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

	// If direction is (0, 0, 0), vector has no direction
	return (*v);

}

int		is_equal(t_point *a, t_point *b)
{
	return ((a->x == b->x) && (a->y == b->y));
}

void	move_point(t_point *a, t_point *offset)
{
	a->x += offset->x;
	a->y += offset->y;
}

t_p3d	p_add(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c,\
	v.x + u.x,\
	v.y + u.y,\
	v.z + u.z);
	return (*c);
}

t_p3d	p_sub(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c,\
	v.x - u.x,\
	v.y - u.y,\
	v.z - u.z);
	return (*c);
}


double	get_len(t_p3d v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

double	get_dist(t_p3d v, t_p3d u)
{
	return (sqrt(pow(v.x - u.x, 2) + pow(v.y - u.y, 2) + pow(v.z - u.z, 2)));
}

t_p3d	scaldiv(t_p3d *c, t_p3d v, double s)
{
	if (s == 0)
	{
		printf("DIVISION BY ZERO ERROR!\n");
		return ((t_p3d){0,0,0});
	}
	init_p3d(c, v.x * pow(s, -1), v.y * pow(s, -1), v.z * pow(s, -1));
	return (*c);
}

t_p3d	scalmult(t_p3d *c, t_p3d v, double s)
{
	init_p3d(c, v.x * s, v.y * s, v.z * s);
	return (*c);
}

t_p3d	normalize(t_p3d *n, t_p3d v)
{
	double len;
	len = get_len(v);
	if (len == 0)
	{
		printf("ZERO VECTOR CAN'T BE NORMALIZED!\n");
		return ((t_p3d){0,0,0});
	}
	
	scaldiv(n, v, len);
	return (*n);
}

double		dot(t_p3d v, t_p3d u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

double		dot_alpha(t_p3d v, double angle)
{
	return (get_len(v) * cos(angle));
}

double		cos_sim(t_p3d v, t_p3d u)
{
	double len_v;
	len_v = get_len(v);
	if (len_v == 0)
	{
		printf("ZERO VECTOR CAN'T BE MEASURED!\n");
		return ((double)NAN);
	}
	return (dot(v, u) * pow(len_v * get_len(u), -1));
}

t_p3d	p_mult(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, v.x * u.x, v.y * u.y, v.z * u.z);
	return (*c);
}

double	det2(t_p2d v, t_p2d u)
{
	return (v.x * u.y - u.x * v.y);
}



t_p3d	cross(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c,
	v.z * u.y - v.y * u.z,\
	v.x * u.z - v.z * u.x,\
	v.y * u.x - v.x * u.y);
	return (*c);
}

int		is_not_zero(t_p3d vec)
{
	return (vec.x || vec.y || vec.z);
}