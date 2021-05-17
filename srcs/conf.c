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
	int	out;

	out = render(conf, rt, *cam);
	if (out != 1)
		return (handle_errors("Render error...'\n"));
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
	else if (keycode == G)
		cam->dir.y -= ARATEY;
	else if (keycode == T)
		cam->dir.y += ARATEY;
	else if (keycode == F)
		cam->dir.x += ARATEX;
	else if (keycode == H)
		cam->dir.x -= ARATEX;
	else
		return (0);
	return (1);
}

int	do_window(t_norm *norm, t_cam *cam)
{
	mlx_clear_window(norm->conf.vars.mlx, norm->conf.vars.win);
	do_render(&norm->conf, &norm->rt, cam);
	mlx_put_image_to_window(norm->conf.vars.mlx, \
	norm->conf.vars.win, \
	norm->conf.img.img, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_norm *norm)
{
	t_cam	*cam;

	if (keycode == ESC)
		close_win(&norm->conf.vars);
	if (keycode == RIGHT || keycode == LEFT)
	{
		if (keycode == RIGHT)
		{
			if (!norm->conf.node->next)
				return (printf("Reached last camera!\n"));
			norm->conf.node = norm->conf.node->next;
		}
		if (keycode == LEFT)
		{
			if (!norm->conf.node->prev)
				return (printf("Reached first camera!\n"));
			norm->conf.node = norm->conf.node->prev;
		}
		return (do_window(norm, (t_cam *)norm->conf.node->content));
	}
	cam = (t_cam *)norm->conf.node->content;
	if (cam_hooks(keycode, cam))
		return (do_window(norm, cam));
	return (0);
}

int	close_win(t_win *vars)
{
	(void)vars;
	exit(0);
	return (0);
}
