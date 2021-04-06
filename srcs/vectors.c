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
	v->loc->x = x;
	v->loc->y = y;
	v->loc->z = z;

	// If direction is (0, 0, 0), vector has no direction
	v->dir->x = 0;
	v->dir->y = 0;
	v->dir->z = 0;
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

void	p_add(t_p3d *c,t_p3d *v, t_p3d *u)
{
	init_p3d(c,\
	v->x + u->x,\
	v->y + u->y,\
	v->z + u->z);
}

void	p_add(t_p3d *c, t_p3d *v, t_p3d *u)
{
	init_v3d(c,\
	v->x - u->x,\
	v->y - u->y,\
	v->z - u->z);
}


double	get_len(t_v3d *v)
{
	return (sqrt(pow(v->loc->x, 2) + pow(v->loc->y, 2) + pow(v->loc->z, 2)));
}


void		scaldiv(t_p3d *c, t_p3d *v, double s)
{
	c = NULL;
	if (s == 0)
	{
		printf("DIVISION BY ZERO ERROR!\n");
		return ;
	}
	init_v3d(c, v->x / s, v->y / s, v->z / s);
}

void		scalmult(t_v3d *c, t_v3d *v, double s)
{
	init_v3d(c, v->loc->x * s, v->loc->y * s, v->loc->z * s);
}

void		normalize(t_p3d *n, t_p3d *v)
{
	n = NULL;
	double len = get_len(v);
	if (len == 0)
	{
		printf("ZERO VECTOR CAN'T BE NORMALIZED!\n");
		return ;
	}
	
	scaldiv(n, v, len);
}

double		dot(t_v3d *v, t_v3d *u)
{
	return (v->loc->x * u->loc->x + v->loc->y * u->loc->y + v->loc->z * u->loc->z);
}

double		dotAlpha(t_v3d *v, double angle)
{
	return (get_len(v) * cos(angle));
}

double		cosSim(t_v3d *v, t_v3d *u)
{
	double lenV = get_len(v);
	if (lenV == 0)
	{
		printf("ZERO VECTOR CAN'T BE MEASURED!\n");
		return ((double)NAN);
	}
	return (dot(v, u) / (lenV * get_len(u)));
}

void		vecMult(t_v3d *c, t_v3d *v, t_v3d *u)
{
	init_v3d(c, v->loc->x * u->loc->x, v->loc->y * u->loc->y, v->loc->z * u->loc->z);
}

double	det2(t_point *v, t_point *u)
{
	return (v->x * u->y - u->x * v->y);
}

void	cross(t_v3d *c, t_v3d *v, t_v3d *u)
{
	init_v3d(c, 
	v->loc->y * u->loc->z - v->loc->z * u->loc->y,\
	v->loc->z * u->loc->x - v->loc->x * u->loc->z,\
	v->loc->x * u->loc->y - v->loc->y * u->loc->x);
}

void	draw_vector(t_vector *v, t_p2d *end, t_conf *conf, void (*put_line)(t_line *, t_conf *))
{
	t_line line;

	init_line(&line, &(t_point){v->loc->x, v->loc->y}, &(t_point){end->x, end->y}, red);
	put_line(&line, conf);
}