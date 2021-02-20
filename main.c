#include "minirt.h"
#include <time.h>
#include "tests.h"

// KEYMAPS:
#define UP   126
#define LEFT 123
#define DOWN 125
#define RIGHT 124
#define ESC	 53


void	put_square (int side, t_point *start, int color, void *mlx_ptr, void* win_ptr)
{
	int i = 0;
	int j = 0;

	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, start->x + i, start->y + j, color);
			j++;
		}
	i++;
	}
}

int key_hook (int keycode, t_vars *vars)
{

	if (keycode == ESC)
		close_win(vars);
	else if (keycode == RIGHT)
		dprintf(1, "RIGHT\n");
	else if (keycode == LEFT)
		dprintf(1, "LEFT\n");
	return (0);
}

int mouse_hook(int button, int x, int y, t_vars *vars)
{
	dprintf(1, "kek\n");
	return (0);
}

int             close_win(t_vars *vars)
{
	exit(0);
}


int main(int argc, char **argv)
{
	t_point start1 = {250, 250};
	t_point start2 = {150, 150};

	t_vars vars;
	t_res RES;

	RES.X = ft_atoi(argv[1]);
	RES.Y = ft_atoi(argv[2]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, RES.X, RES.Y, "My window");
	
	put_square(50, &start1, cyan, vars.mlx, vars.win);

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L<<17, close_win, &vars);
	mlx_loop(vars.mlx);
}
