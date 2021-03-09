#include "minirt.h"

static int	is_in(t_point *point, t_circle *circle)
{
	double res;

	res = pow((double)circle->rad, 2.0);

	if ((pow((double)point->x, 2.0) + pow((double)point->y, 2.0)) <= res)
		return (1);
	return (0);
}

void		init_circle(t_circle *circle, int rad, int color, t_point *center)
{
	circle->rad = rad;
	circle->color = color;
	circle->center = center;
}

void		put_circle(t_circle *circle, t_conf *conf)
{
	int i;
	int j;

	i = -circle->rad;
	j = -circle->rad;
	
	while (i < circle->rad)
	{
		j = -circle->rad;
		while (j < circle->rad)
		{
			if (is_in(&(t_point){j, i}, circle))
				my_mlx_pixel_put(conf->img, j + circle->center->x, i + circle->center->y, circle->color);
				// mlx_pixel_put(vars->mlx, vars->win, j, i, circle->color);
			j++;
		}
	i++;
	}
}