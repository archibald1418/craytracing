#include "minirt.h"
#include "tests.h"
#include <time.h>

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void			calc_square(t_params *params)
{
	t_square *square;

	square = params->square;
	
	if (square->start->x <= 0 || \
		square->start->x + square->side >= params->res->X)
		params->speed->x *= -1;
	else if (square->start->y <= 0 || \
		square->start->y + square->side >= params->res->Y)
		params->speed->y *= -1;

	square->start->y += params->speed->y;
	square->start->x += params->speed->x;
}

int     render_next_frame(t_params *params)
{
	t_square *square;

	square = params->square;
	
	calc_square(params);

	mlx_clear_window(params->vars->mlx, params->vars->win);
	mlx_put_image_to_window(params->vars->mlx, params->vars->win, params->data->img, square->start->x, square->start->y);
	return (0);
}

int main()
{
	t_point start1 = {250, 250};
	t_point start2 = {150, 150};

	t_win vars;
	t_res RES;

	t_data data;

	t_circle circle;

	t_square square;

	RES.X = ft_atoi("500");
	RES.Y = ft_atoi("500");

	init_window(&vars, &RES, "My window!");
	init_img(&data, &vars, RES.X, RES.Y);

	init_circle(&circle, 200, cyan, &start1);
	put_circle(&circle, &vars, &data);

	// init_square(&square, 40, cyan, &start1);
	// put_square(&square, &vars, &data);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, start1.x, start1.y);
	// init_square(&square, 5, cyan, &start1);
	// put_square(&square, &vars, &data);



	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	// mlx_loop_hook(vars.mlx, render_next_frame, &params);
	mlx_loop(vars.mlx);
}
