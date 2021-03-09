#include "minirt.h"

typedef struct	s_args
{
	t_point *point;
	t_conf	*conf;
}				t_args;


int get_mouse_pos(int x, int y, t_args *args)
{
	args->point->x = x;
	args->point->y = y;

	if (0 <= x && x <= args->conf->res->X && \
		0 <= y && y <= args->conf->res->Y)
	{
		dprintf(1, "posx=%d, posy=%d\n", args->point->x, args->point->y);
		mlx_clear_window(args->conf->vars->mlx, args->conf->vars->win);
		put_text(args->conf, ft_strjoin(ft_strjoin("posx=", ft_itoa(x)), ft_strjoin(" posy=", ft_itoa(y))));
	}
	return (0);
}

int main()
{
	t_point start1 = {100, 100};
	t_point start2 = {150, 150};
	t_point starts = {0, 0};

	t_win	vars;
	t_res	res;
	t_data	img;

	t_conf	conf;

	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");

	// conf = (t_conf){&img, &vars, &res};
	// init_window(conf.vars, conf.res, "Line translate!");
	// init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);

	t_point point;
	conf = (t_conf){&img, &vars, &res};
	t_args args = {&point, &conf};
	init_window(&vars, &res, "Test mouse!");

	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(conf.vars->win, mouse_hook, NULL);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, get_mouse_pos, &args);
	// mlx_loop_hook(vars.mlx, render_next_frame, &params);
	mlx_loop(vars.mlx);
}

