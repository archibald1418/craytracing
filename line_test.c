#include "minirt.h"
#include "tests.h"
#include <time.h>

int main()
{
	t_point start1 = {100, 100};
	t_point start2 = {150, 150};
	t_point starts = {0, 0};

	t_win vars;
	t_res RES;

	t_data data;

	t_line line;

	RES.X = ft_atoi("1000");
	RES.Y = ft_atoi("1000");

	init_line(&line, &start1, &start2, orange);

	put_line_naive(&line, &vars, &data);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 400, 400);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_loop(vars.mlx);	
}