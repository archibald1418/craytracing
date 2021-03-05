#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minirt.h"

void	put_text(t_conf *conf, char *str)
{
	mlx_string_put(conf->vars->mlx, conf->vars->win, 100, 100, white, str);
}

void	test_text(t_conf *conf)
{
	char *str = {"Hello bichez!"};

	put_text(conf, str);
}

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
	
	// test_addition(&conf);

	test_text(&conf);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_loop(vars.mlx);
}