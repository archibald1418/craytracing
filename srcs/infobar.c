#include "minirt.h"

int	put_mouse_pos(int x, int y, t_args *args)
{
	char	pos[100];
	char	col[100];
	int		rgbval;

	if (0 <= x && x <= args->conf->res.X && \
		0 <= y && y <= args->conf->res.Y)
	{
		mlx_clear_window(args->conf->vars.mlx, args->outwin);
		sprintf((char *)pos, "x=%-4d y=%-4d", x, y);
		put_text(args->conf->vars.mlx, args->outwin, pos, &(t_point){10, 30});
		rgbval = my_mlx_pixel_get(&args->conf->img, x, y);
		sprintf((char *)col, "r=%-3d g=%-3d b=%-3d", \
		get_r(rgbval), \
		get_g(rgbval), \
		get_b(rgbval));
		put_text(args->conf->vars.mlx, args->outwin, col, &(t_point){10, 70});
		sprintf((char *)col, "#%08x", rgbval);
		put_text(args->conf->vars.mlx, args->outwin, col, &(t_point){10, 100});
	}
	return (0);
}

void	*init_infobar(void *mlx, int sizex, int sizey, char *title)
{
	void	*infobar;

	infobar = mlx_new_window(mlx, sizex, sizey, title);
	return (infobar);
}
