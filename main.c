#include <stdio.h>
#include "mlx.h"
#include "libft.h"

int func(int a, int b);

int main(int argc, char **argv)
{
	void *pa;
	void *pb;

	pa = mlx_init();
	pb = mlx_new_window(pa, ft_atoi(argv[1]), ft_atoi(argv[2]), "My window");
	mlx_pixel_put(pa, pb, 250, 250, 0x00BF7230);

	mlx_hook(pb, 0, 0, &func, NULL);
	mlx_loop(pa);
}

int func(int a, int b)
{
	return (printf("aaa"));
}