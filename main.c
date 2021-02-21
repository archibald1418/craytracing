#include "minirt.h"
#include <time.h>
#include "tests.h"

// KEYMAPS:
#define UP   126
#define LEFT 123
#define DOWN 125
#define RIGHT 124
#define ESC	 53

// EVENTS
 #define DestroyNotify 17
 #define StructureNotifyMask 1L<<17


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	put_square (t_square *square, t_vars *vars, t_data *data)
{
	int i = 0;
	int j = 0;

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

int mouse_hook(int button, int x, int y, t_vars *vars)
{
	dprintf(1, "kek\n");
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
	if (square->start->x + square->side >= params->res->X)
		params->speed->x = -5;

	if (square->start->y + square->side >= params->res->Y)
		params->speed->y = -5;

	if (square->start->x <= 0)
		params->speed->x = 5;
	if (square->start->y <= 0)
		params->speed->y = 5;

	square->start->y += params->speed->y;
	square->start->x += params->speed->x;

	mlx_clear_window(params->vars->mlx, params->vars->win);
	mlx_put_image_to_window(params->vars->mlx, params->vars->win, params->data->img, square->start->x, square->start->y);
	return (0);
}

void	init_square(t_square *square, int side, int color, t_point *start)
{
	square->side = side;
	square->color = color;
	square->start = start;
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
