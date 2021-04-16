#include "minirt.h"

int key_hook (int keycode, t_win *vars)   
{

	if (keycode == ESC)
		close_win(vars);
	else if (keycode == RIGHT)
		dprintf(1, "RIGHT\n");
	else if (keycode == LEFT)
		dprintf(1, "LEFT\n");
	return (0);
}

int             close_win(t_win *vars)
{
	/*
	TODO: mlx_destroy_window + mlx_destroy_image
	helps with leaks
	NOTE to self: I have two windows :)
	*/
	exit(0);
	return (0);
}

void	init_window(t_win *vars, t_res *RES, char *title)
{
	int maxresx;
	int maxresy;

	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &maxresx, &maxresy);
	printf("%d - %d\n", maxresx, maxresy);
	RES->X = (int)fmin(maxresx, RES->X);
	RES->Y = (int)fmin(maxresx, RES->Y);

	vars->win = mlx_new_window(vars->mlx, RES->X, RES->Y, title);
}

void	init_img(t_data *data, t_win *vars, int width, int height)
{
	data->img = mlx_new_image(vars->mlx, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

unsigned int	my_mlx_pixel_get(t_data *data, int x, int y)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

void	put_text(void *mlx, void *win, char *str, t_point *loc)
{
	mlx_string_put(mlx, win, loc->x, loc->y, white, str);
}