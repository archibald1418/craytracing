#include "minirt.h"
#include "tests.h"
#include <time.h>

int main()
{
	t_point start1 = {100, 100};
	t_point start2 = {150, 15};

	t_win vars;
	t_res RES;

	t_data data;

	t_line line1;
	t_line line2;

	RES.X = ft_atoi("1000");
	RES.Y = ft_atoi("1000");


	//TODO: test funcs
	t_point start3 = {1, 1};
	t_point start4 = {RES.X - 1, RES.Y - 1};

	t_point s5 = {300, 400};
	t_point s6 = {100, 200};

	init_window(&vars, &RES, "My window!");
	init_img(&data, &vars, RES.X, RES.Y);

	init_line(&line1, &start3, &start4, orange);
	init_line(&line2, &start1, &start2, magenta);

	put_line_naive(&line1, &vars, &data);
	put_line_naive(&line2, &vars, &data);

	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_loop(vars.mlx);
}