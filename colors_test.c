#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minirt.h"




// Adding colors test

void	test_addition(t_conf *conf)
{
	int c1 = violet;
	int c2 = gray;

	int c3 = yellow;
	int c4 = magenta;

	t_square s1;
	t_square s2;

	s1 = (t_square){&(t_point){100, 100}, 100, c1};
	s2 = (t_square){&(t_point){200, 100}, 100, c2};

	put_square(&s1, conf);
	put_square(&s2, conf);

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

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;

	t_conf	conf;

	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");

	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, "Color addition!");
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	test_addition(&conf);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_loop(vars.mlx);
}