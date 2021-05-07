#include "minirt.h"

void	init_square(t_square *square, int side, int color, t_point *start)
{
	square->side = side;
	square->color = color;
	square->start = start;
}

void	put_square (t_square *square, t_conf *conf)
{
	int i;
	int j;
	unsigned int tmp;

	tmp = square->color;
	i = square->start->y;
	j = square->start->x;
	while (i < square->start->y + square->side)
	{
		j = square->start->x;
		while (j < square->start->x + square->side)
		{
			if ((tmp = my_mlx_pixel_get(&conf->img, j, i)) == black)
				tmp = square->color;
			my_mlx_pixel_put(&conf->img, j, i, add_trgb(square->color, tmp));
			j++;
		}
	i++;
	}
}


// void	put_square_lines (t_square *square, t_point *lowleft, t_win *vars, t_data *data, void (*put_line)(t_line *, t_win *, t_data *))
// {
// 	t_line edge;
// 	int i;
// 	int yi;

// 	init_line(&edge, square->start, lowleft, square->color);
// 	i = 0;
// 	yi = 

// 	while (i < square->side)
// 	{
// 		put_line(&edge, vars, data);
// 		edge->A->
// 		i++;
// 	}
	
	
// }