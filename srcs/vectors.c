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
	v->x = x;
	v->y = y;
	v->z = z;
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

t_v3d	*vecAdd(t_v3d *v, t_v3d *u)
{
	t_v3d c;

	init_v3d(&c, v->x + u->x, v->y + u->y, v->z + u->z);
	return (&c);
}

t_v3d	*vecSub(t_v3d *v, t_v3d *u)
{
	t_v3d c;

	init_v3d(&c, v->x - u->x, v->y - u->y, v->z - u->z);
	return (&c);
}

double	get_len(t_v3d *v)
{
	return (sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2)));
}


void		scaldiv(t_v3d *u, t_v3d *v, double s)
{
	if (s == 0)
	{
		printf("DIVISION BY ZERO ERROR!\n");
		return (NULL);
	}
	init_v3d(u, v->x / s, v->y / s, v->z / s);
}

void		scalmult(t_v3d *u, t_v3d *v, double s)
{
	init_v3d(u, v->x * s, v->y * s, v->z * s);
}

void		normalize(t_norm3d *n, t_v3d *v)
{
	double len = get_len(v);
	if (len == 0)
	{
		printf("ZERO VECTOR CAN'T BE NORMALIZED!\n");
		return (NULL);
	}
	
	return (scaldiv(v, n, len));
}

double		dot(t_v3d *v, t_v3d *u)
{
	return (v->x * u->x + v->y * u->y + v->z * u->z);
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

void		vecMult(t_v3d *v, t_v3d *u)
{
	t_v3d c;

	init_v3d(&c, v->x * u->x, v->y * u->y, v->z * u->z);

	return (&c);
}

double	det2(t_point *v, t_point *u)
{
	return (v->x * u->y - u->x * v->y);
}

void	cross(t_v3d *c, t_v3d *v, t_v3d *u)
{
	init_vec3d(c, 
	v->y * u->z - v->z * u->y,\
	v->z * u->x - v->x * u->z,\
	v->x * u->y - v->y * u->x);
}

void	draw_vector(t_vector *vec, t_conf *conf, void* put_line(t_line*, t_conf*), int scalar)
{
	double len = get_len(vec->loc);
	t_line line;
	t_point end;

	end = (t_point){vec->dir->x * scalar + vec->loc->x, vec->dir->y * scalar + vec->loc->y};

	init_line(&line, vec->loc, &end, white);
	put_line(&line, conf);
	
}