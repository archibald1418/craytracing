#include "tests.h"

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;

	t_conf	conf;
	t_args args;

	char *test = "LINES DDA!";

	// Window
	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");
	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, test);
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// Infobar
	args.outwin = init_infobar(conf.vars->mlx, 210, 210, "RGB");
	args.conf = &conf;

	// test_addition(&conf);

	test_lines(&conf, put_line_dda);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_hook(args.outwin, DestroyNotify, StructureNotifyMask, close_win, &args);
	mlx_loop(vars.mlx);
}