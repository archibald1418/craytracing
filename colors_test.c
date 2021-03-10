#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minirt.h"

typedef struct	s_args
{
	void *outwin;
	t_conf	*conf;
}				t_args;


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

// int     render_next_frame(t_params *params)
// {
// 	t_square *square;

// 	square = params->square;
	
// 	calc_square(params);

// 	mlx_clear_window(params->vars->mlx, params->vars->win);
// 	mlx_put_image_to_window(params->vars->mlx, params->vars->win, params->data->img, square->start->x, square->start->y);
// 	return (0);
	
// }

// int main()
// {
// 	double ratio = drand48();
// 	double alpha = ratio * 255;

// 	int i = 0;
// 	while (i < 20)
// 	{
// 		printf("ratio -> %f\talpha -> %f\t->\t%d\n", ratio, alpha, (int)alpha);
// 		i++;
// 		ratio = drand48();
// 		alpha = ratio * 255;
// 	}
// }

int put_mouse_pos(int x, int y, t_args *args)
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

void	*init_infobar(void *mlx)
{
	void *infobar = mlx_new_window(mlx, 210, 210, "Coords!");
	return (infobar);
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