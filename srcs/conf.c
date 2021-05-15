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

#ifndef ARATEX 
# define ARATEX 0.1
#endif

#ifndef ARATEY
# define ARATEY 0.1
#endif

#ifndef ARATEZ
# define ARATEZ 0.1
#endif

int	do_render(t_conf *conf, t_rt *rt, t_cam *cam)
{
	int out;
	out = render(conf, rt, *cam);
	if (out != 1)
		return (printf("Render error...'\n"));
	return (0);
}
int	cam_hooks(int keycode, t_cam *cam)
{
	if (keycode == WKEY)
		cam->loc.y += RATEY;
	else if (keycode == AKEY)
		cam->loc.x -= RATEX;
	else if (keycode == SKEY)
		cam->loc.y -= RATEY;
	else if (keycode == DKEY)
		cam->loc.x += RATEX;
	else if (keycode == UP)
		cam->loc.z += RATEZ;
	else if (keycode == DOWN)
		cam->loc.z -= RATEZ;
	else if (keycode == NUM2)
		cam->dir.y -= ARATEY;
	else if (keycode == NUM8)
		cam->dir.y += ARATEY;
	else if (keycode == NUM4)
		cam->dir.x += ARATEX;
	else if (keycode == NUM6)
		cam->dir.x -= ARATEX;
	else if (keycode == NUMPLUS)
		cam->dir.z += ARATEZ;
	else if (keycode == NUMMINUS)
		cam->dir.z -= ARATEZ;
	else
		return (0);
	return (1);
}

int key_hook (int keycode, t_norm *norm)   
{
	t_cam *cam;

	if (keycode == ESC)
		close_win(&norm->conf.vars);

	// Flick through cameras
	if (keycode == RIGHT || keycode == LEFT)
	{
		if (keycode == RIGHT)
		{
			if (!norm->conf.node->next)
				return(printf("Reached last camera!\n"));
			norm->conf.node = norm->conf.node->next;
		}
		if (keycode == LEFT)
		{
			if (!norm->conf.node->prev)
				return(printf("Reached first camera!\n"));
			norm->conf.node = norm->conf.node->prev;
		}
		mlx_clear_window(norm->conf.vars.mlx, norm->conf.vars.win);
		do_render(&norm->conf, &norm->rt, (t_cam *)norm->conf.node->content);
		mlx_put_image_to_window(norm->conf.vars.mlx, norm->conf.vars.win, norm->conf.img.img, 0, 0);
		return (1);
	}
	cam = (t_cam *)norm->conf.node->content;
	if (cam_hooks(keycode, cam))
	{
		mlx_clear_window(norm->conf.vars.mlx, norm->conf.vars.win);
		do_render(&norm->conf, &norm->rt, cam);
		mlx_put_image_to_window(norm->conf.vars.mlx, norm->conf.vars.win, norm->conf.img.img, 0, 0);
	}
	// Move camera
	// FIXME: x & y axes inverted with movement lol)))

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
	// mlx_destroy_image()
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
	// printf("%d -> ")
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