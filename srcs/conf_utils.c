#include "minirt.h"

void	init_window(t_win *vars, t_res *res, char *title)
{
	int	maxresx;
	int	maxresy;

	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &maxresx, &maxresy);
	res->X = (int)fmin(maxresx, res->X);
	res->Y = (int)fmin(maxresx, res->Y);
	vars->win = mlx_new_window(vars->mlx, res->X, res->Y, title);
}

void	init_img(t_data *data, t_win *vars, int width, int height)
{
	data->img = mlx_new_image(vars->mlx, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
	&data->line_length, \
	&data->endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_text(void *mlx, void *win, char *str, t_point *loc)
{
	mlx_string_put(mlx, win, loc->x, loc->y, white, str);
}
