#include "minirt.h"
#include "tests.h"


void	test_triangle(t_conf *conf, void (*put_line)(t_line *, t_conf *))
{
	t_triangle tr1;
	t_point p11;
	t_point p12;
	t_point p13;

	// p11 = (t_point){100, 100};
	// p12 = (t_point){100, 300};
	// p13 = (t_point){300, 100};
	p11 = (t_point){200, 100};
	p12 = (t_point){120, 700};
	p13 = (t_point){500, 100};

	init_triangle(&tr1, &p11, &p12, &p13, blue);
	put_triangle(&tr1, conf, put_line);

	// t_triangle tr2;
	// t_line l21;
	// t_line l22;
	// t_line l23;
}

void test_translate_triangle(t_conf *conf, void (*put_line)(t_line *, t_conf *))
{

	t_triangle tr1;
	t_point p11;
	t_point p12;
	t_point p13;

	t_grad rate = {1, 1};

	// Slant +
	t_grad tmp[sizeof(t_grad)];

	p11 = (t_point){500, 200};
	p12 = (t_point){150, 700};
	p13 = (t_point){100, 100};

	init_triangle(&tr1, &p11, &p12, &p13, magenta);
	put_triangle(&tr1, conf, put_line);

	ft_memcpy(tmp, &rate, sizeof(t_grad));

	int side = 100;
	int i = 0;
	while (i < side)
	{
		translate_triangle(&tr1, (t_grad *)&tmp, conf, put_line); // TODO: move coords func + translate_line
		i++;
	}
}

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;
	t_args args;

	t_conf	conf;

	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");

	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, "Line dda!");
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// put_square(&(t_square){&(t_point){0, 0}, res.X, white}, &conf);
	// Test lines!

	// Infobar
	args.outwin = init_infobar(conf.vars->mlx, 500, 500, "Triangle!");
	args.conf = &conf;

	// test_translate(&conf, put_line_naive);
	// test_lines(&conf, put_line_dda);
	// test_triangle(&conf, put_line_dda);
	test_translate_triangle(&conf, put_line_dda);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_loop(vars.mlx);
}