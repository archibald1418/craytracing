#include "tests.h"



// Adding colors test

void	test_addition(t_conf *conf)
{
	int c1 = violet;
	int c2 = gray;

	int c3 = yellow;
	int c4 = magenta;

	t_square s1;
	t_square s2;

	t_circle cr1;
	t_circle cr2;

	s1 = (t_square){&(t_point){100, 100}, 100, c1};
	s2 = (t_square){&(t_point){150, 100}, 100, c2};

	cr1 = (t_circle){&(t_point){conf->res->X/2, conf->res->Y/2}, 50, yellow};
	cr2 = (t_circle){&(t_point){cr1.center->x + 40, cr1.center->y}, 50, magenta};

	put_square(&s1, conf);
	put_square(&s2, conf);
	put_circle(&cr1, conf);
	put_circle(&cr2, conf);

}

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;

	t_conf	conf;
	t_args args;

	// Window
	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");
	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, "Color addition!");
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// Infobar
	args.outwin = init_infobar(conf.vars->mlx);
	args.conf = &conf;

	test_addition(&conf);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_hook(args.outwin, DestroyNotify, StructureNotifyMask, close_win, &args);
	mlx_loop(vars.mlx);
}