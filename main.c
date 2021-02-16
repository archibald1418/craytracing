#include "minilibx_mms_20200219/mlx.h"
#include <stdio.h>
#include "libft.h"

int func(int a, int b);

int main(int argc, char **argv)
{
	void *pa;
	void *pb;

	pa = mlx_init();
	pb = mlx_new_window(pa, ft_atoi(argv[1]), ft_atoi(argv[2]), "My window");
	mlx_pixel_put(pa, pb, 0xffaaffaa);

	mlx_hook(pb, &func);
	mlx_loop(pa);
}

int func(int a, int b)
{
	return (printf("aaa"));
}