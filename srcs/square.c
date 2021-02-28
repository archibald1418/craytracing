#include "minirt.h"

void	init_square(t_square *square, int side, int color, t_point *start)
{
	square->side = side;
	square->color = color;
	square->start = start;
}

void	put_square (t_square *square, t_win *vars, t_data *data)
{
	int i;
	int j;

	i = square->start->y;
	j = square->start->x;
	while (i < square->start->y + square->side)
	{
		j = square->start->x;
		while (j < square->start->x + square->side)
		{
			my_mlx_pixel_put(data, j, i, square->color);
			j++;
		}
	i++;
	}
}