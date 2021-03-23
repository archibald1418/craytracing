#include "minirt.h"
#include "tests.h"

typedef struct s_args2
{
	t_v3d	*a;
	
}

int put_vec_pos(int x, int y, t_args *args)
{
	char pos[100];
	char col[100];

	if (0 <= x && x <= args->conf->res->X && \
		0 <= y && y <= args->conf->res->Y)
	{
		dprintf(1, "posx=%d, posy=%d\n", x, y);
		mlx_clear_window(args->conf->vars->mlx, args->outwin);

		// Put position
		sprintf((char *)pos, "x=%-4d y=%-4d", x, y);
		dprintf(1, "%s", pos);
		put_text(args->conf->vars->mlx, args->outwin, pos, &(t_point){10, 30});

		// Put color
		int rgbval = my_mlx_pixel_get(args->conf->img, x, y);
		sprintf((char *)col, "r=%-3d g=%-3d b=%-3d", get_r(rgbval), get_g(rgbval), get_b(rgbval));
		dprintf(1, "%s", col);
		put_text(args->conf->vars->mlx, args->outwin, col, &(t_point){10, 70});

		// Put hex color
		sprintf((char *)col, "#%X", rgbval);
		put_text(args->conf->vars->mlx, args->outwin, col, &(t_point){10, 100});

	}
	return (0);
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
	args.outwin = init_infobar(conf.vars->mlx);
	args.conf = &conf;

	// test_translate(&conf, put_line_naive);
	test_lines(&conf, put_line_dda);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_loop(vars.mlx);
}