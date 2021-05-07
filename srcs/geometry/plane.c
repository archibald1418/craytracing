#include "minirt.h"

void 	init_plane(t_plane *p, t_line *a, t_line *b, int color)
{
	p->a = a;
	p->b = b;
	p->color = color;
}

void	put_plane(t_plane *p, t_conf *conf)
{
	// TODO: we assume that lines are parallel
	// BUT that also means this func can draw a trapezoid

	/* TODO: In perspective, trapezoid is a midstate between a parallelogram and a triangle!*/
	// if (!are_parallel())
	;
	(void)p;
	(void)conf;
}