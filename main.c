#include "minirt.h"
#include "tests.h"
#include <time.h>

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
	t_point start1 = {100, 100};
	t_point start2 = {150, 150};
	t_point starts = {0, 0};

	t_win vars;
	t_res RES;

	t_data data;

	t_circle circle;

	t_square square;

	RES.X = ft_atoi("3000");
	RES.Y = ft_atoi("3000");

	init_window(&vars, &RES, "My window!");

	init_circle(&circle, 100, cyan3, &start1);

	init_img(&data, &vars, circle.rad * 2, circle.rad * 2);
	
	init_square(&square, circle.rad*2, magenta, &starts);
	put_square(&square, &vars, &conf);
	put_circle(&circle, &vars, &conf);

	init_square(&square, 40, cyan, &start1);
	put_square(&square, &vars, &data);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 200, 200);
	// init_square(&square, 5, cyan, &start1);
	// put_square(&square, &vars, &data);

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	// mlx_loop_hook(vars.mlx, render_next_frame, &params);
	mlx_loop(vars.mlx);
}
