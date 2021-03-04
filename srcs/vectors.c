#include "minirt.h"


int		is_equal(t_point *a, t_point *b)
{
	return ((a->x == b->x) && (a->y == b->y));
}

void	move_point(t_point *a, t_point *offset)
{
	a->x += offset->x;
	a->y += offset->y;
}