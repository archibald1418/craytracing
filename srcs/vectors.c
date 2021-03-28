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

void	vecAdd(t_v3d *c,t_v3d *v, t_v3d *u)
{
	init_v3d(c,\
	v->loc->x + u->loc->x,\
	v->loc->y + u->loc->y,\
	v->loc->z + u->loc->z);
}

void	vecSub(t_v3d *c, t_v3d *v, t_v3d *u)
{
	init_v3d(c,\
	v->loc->x - u->loc->x,\
	v->loc->y - u->loc->y,\
	v->loc->z - u->loc->z);
}

double	get_len(t_v3d *v)
{
	return (sqrt(pow(v->loc->x, 2) + pow(v->loc->y, 2) + pow(v->loc->z, 2)));
}


void		scaldiv(t_v3d *c, t_v3d *v, double s)
{
	c = NULL;
	if (s == 0)
	{
		printf("DIVISION BY ZERO ERROR!\n");
		return ;
	}
	init_v3d(c, v->loc->x / s, v->loc->y / s, v->loc->z / s);
}

void		scalmult(t_v3d *c, t_v3d *v, double s)
{
	init_v3d(c, v->loc->x * s, v->loc->y * s, v->loc->z * s);
}

void		normalize(t_v3d *n, t_v3d *v)
{
	n = NULL;
	double len = get_len(v);
	if (len == 0)
	{
		printf("ZERO VECTOR CAN'T BE NORMALIZED!\n");
		return ;
	}
	
	scaldiv(n, v, len);
	// n->loc = &(t_p3d){0, 0};
	//FIXME: if normal is a vector what location should it have?? (or should it??)
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