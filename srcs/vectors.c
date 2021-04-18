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

void	init_p3d(t_p3d *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}



void	init_v3d(t_v3d *v, double x, double y, double z)
{
	v->loc.x = x;
	v->loc.y = y;
	v->loc.z = z;

	// If direction is (0, 0, 0), vector has no direction
	v->dir.x = 0;
	v->dir.y = 0;
	v->dir.z = 0;
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

void	p_add(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c,\
	v.x + u.x,\
	v.y + u.y,\
	v.z + u.z);
}

void	p_sub(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c,\
	v.x - u.x,\
	v.y - u.y,\
	v.z - u.z);
}


double	get_len(t_p3d v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}


void		scaldiv(t_p3d *c, t_p3d v, double s)
{
	if (s == 0)
	{
		printf("DIVISION BY ZERO ERROR!\n");
		return ;
	}
	init_p3d(c, v.x / s, v.y / s, v.z / s);
}

void		scalmult(t_p3d *c, t_p3d v, double s)
{
	init_p3d(c, v.x * s, v.y * s, v.z * s);
}

void		normalize(t_p3d *n, t_p3d v)
{
	double len;
	len = get_len(v);
	if (len == 0)
	{
		printf("ZERO VECTOR CAN'T BE NORMALIZED!\n");
		return ;
	}
	
	scaldiv(n, v, len);
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
	return (dot(v, u) / (len_v * get_len(u)));
}

void		p_mult(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, v.x * u.x, v.y * u.y, v.z * u.z);
}

double	det2(t_p2d v, t_p2d u)
{
	return (v.x * u.y - u.x * v.y);
}

void	cross(t_p3d *c, t_p3d v, t_p3d u)
{
	init_p3d(c, 
	v.y * u.z - v.z * u.y,\
	v.z * u.x - v.x * u.z,\
	v.x * u.y - v.y * u.x);
}
