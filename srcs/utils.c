#include "minirt.h"

double	calc_der(t_line *a)
{
	int dx;
	int dy;
	double res;

	dx = a->A->x - a->B->x;
	dy = a->A->y - a->B->y;	
	res = abs(dy/dx);
	return (res);	
}

void	put_text(void *mlx, void *win, char *str, t_point *loc)
{
	mlx_string_put(mlx, win, loc->x, loc->y, white, str);
}

double	sign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
}
