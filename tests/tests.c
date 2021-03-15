#include "tests.h"

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