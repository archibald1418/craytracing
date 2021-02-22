#include "minirt.h"
#include "tests.h"
#include <time.h>

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int key_hook (int keycode, t_vars *vars)
{

	if (keycode == ESC)
		close_win(vars);
	else if (keycode == RIGHT)
		dprintf(1, "RIGHT\n");
	else if (keycode == LEFT)
		dprintf(1, "LEFT\n");
	return (0);
}

int             close_win(t_vars *vars)
{
	exit(0);
	return (0);
}

int     render_next_frame(t_params *params)
{
	t_square *square;

	square = params->square;
	
	// square->start->x++;
	// square->start->y++;
	//TODO: перенести расчеты отсюда 
	// TODO: перенести в image

	if (square->start->x <= 0 || \
		square->start->x + square->side >= params->res->X)
		params->speed->x *= -1;
	else if (square->start->y <= 0 || \
		square->start->y + square->side >= params->res->Y)
		params->speed->y *= -1;

	square->start->y += params->speed->y;
	square->start->x += params->speed->x;

	mlx_clear_window(params->vars->mlx, params->vars->win);
	mlx_put_image_to_window(params->vars->mlx, params->vars->win, params->data->img, square->start->x, square->start->y);
	return (0);
}

int main()
{
	t_point start1 = {280, 250};
	t_point start2 = {150, 150};

	t_vars vars;
	t_res RES;

	t_square	square;
	t_point speed = {5, 5};

	t_data data;
	init_square(&square, 50, cyan, &start1);

	t_params params = {&square, &vars, &RES, &speed, &data};

	RES.X = ft_atoi("500");
	RES.Y = ft_atoi("700");

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, RES.X, RES.Y, "My window");

	data.img = mlx_new_image(vars.mlx, 50, 50);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	
	put_square(&square, &vars, &data);

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);

	mlx_loop_hook(vars.mlx, render_next_frame, &params);
	mlx_loop(vars.mlx);
}
