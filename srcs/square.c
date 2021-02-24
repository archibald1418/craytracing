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

	i = 0;
	j = 0;
	while (i < square->side)
	{
		j = 0;
		while (j < square->side)
		{
			my_mlx_pixel_put(data, j, i, square->color);
			j++;
		}
	i++;
	}
}