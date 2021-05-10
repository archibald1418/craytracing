#include "minirt.h"

#ifndef RATEX
# define RATEX 0.5
#endif

#ifndef RATEY
# define RATEY 0.5
#endif

#ifndef RATEZ
# define RATEZ 5
#endif

int	do_render(t_conf *conf, t_rt *rt, t_cam *cam)
{
	int out;
	out = render(conf, rt, *cam);
	if (out != 1)
		return (printf("Render error...'\n"));
	return (0);
}

int key_hook (int keycode, t_norm *norm)   
{
	t_cam *cam;

	ft_bzero(norm->conf.img.addr, sizeof(char) * norm->conf.img.line_length * norm->conf.res.X);
	if (keycode == ESC)
		close_win(&norm->conf.vars);

	// Flick cameras
	if (keycode == RIGHT || keycode == LEFT)
	{
		if (keycode == RIGHT)
		{
			if (!norm->conf.node->next)
				return (0);
			norm->conf.node = norm->conf.node->next;
		}
		if (keycode == LEFT)
		{
			if (!norm->conf.node->prev)
				return (0);
			norm->conf.node = norm->conf.node->prev;
		}
		do_render(&norm->conf, &norm->rt, (t_cam *)norm->conf.node->content);
		mlx_put_image_to_window(norm->conf.vars.mlx, norm->conf.vars.win, norm->conf.img.img, 0, 0);
		return (1);
	}
	cam = (t_cam *)norm->conf.node->content;
	// Move camera
	// FIXME: x & y axes inverted with movement lol)))
	if (keycode == WKEY)
		cam->loc.y += RATEY;
	if (keycode == AKEY)
		cam->loc.x -= RATEX;
	if (keycode == SKEY)
		cam->loc.y -= RATEY;
	if (keycode == DKEY)
		cam->loc.x += RATEX;
	if (keycode == UP)
		cam->loc.z += RATEZ;
	if (keycode == DOWN)
		cam->loc.z -= RATEZ;
	do_render(&norm->conf, &norm->rt, cam);
	mlx_put_image_to_window(norm->conf.vars.mlx, norm->conf.vars.win, norm->conf.img.img, 0, 0);
	return (0);
}


int             close_win(t_win *vars)
{
	(void)vars;
	/*
	TODO: mlx_destroy_window + mlx_destroy_image
	helps with leaks
	NOTE to self: I have two windows :)
	*/
	// TODO: clear all structs and stuff
	exit(0);
	return (0);
}

void	init_window(t_win *vars, t_res *res, char *title)
{
	int maxresx;
	int maxresy;

	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &maxresx, &maxresy);
	res->X = (int)fmin(maxresx, res->X);
	res->Y = (int)fmin(maxresx, res->Y);

	vars->win = mlx_new_window(vars->mlx, res->X, res->Y, title);
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