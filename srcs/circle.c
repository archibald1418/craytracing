#include "minirt.h"

static int	is_in(t_point *point, t_circle *circle)
{
	int res;

	res = pow(circle->rad, 2);

	if ((pow(point->x - circle->rad, 2) + pow(point->y - circle->rad, 2)) <= res)
		return (1);
	return (0);
}

void		init_circle(t_circle *circle, int rad, int color, t_point *center)
{
	circle->rad = rad;
	circle->color = color;
	circle->center = center;
}

void		put_circle(t_circle *circle, t_win *vars, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	while (i < circle->center->y + circle->rad)
	{
		j = 0;
		while (j < circle->center->x + circle->rad)
		{
			if (is_in(&(t_point){i, j}, circle))
				my_mlx_pixel_put(data, j, i, circle->color);
				// mlx_pixel_put(vars->mlx, vars->win, j, i, circle->color);
			j++;
		}
	i++;
	}
}