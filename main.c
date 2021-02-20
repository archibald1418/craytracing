#include "minirt.h"
#include <time.h>
#include "tests.h"

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

int		func(int a, int b)
{
	return (printf("aaa"));
}


int main(int argc, char **argv)
{
	t_point start1 = {250, 250};
	t_point start2 = {150, 150};

	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, ft_atoi(argv[1]), ft_atoi(argv[2]), "My window");
	// put_square(150, &start2, lightblue, pa, pb);
	put_square(50, &start1, get_opposite(add_shade(cyan, 0.9)), vars.mlx, vars.win);

	mlx_hook(vars.win, 0, 0, &func, NULL);
	mlx_loop(vars.mlx);
}
