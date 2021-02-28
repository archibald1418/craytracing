#include "minirt.h"

static int	get_sign(int x)
{
	if (x < 0)
		return (-1);
	if (x > 0)
		return (1);
	return (0);
}

void	init_line(t_line *line, t_point *A, t_point *B, int color)
{
	line->A = A;
	line->B = B;
	line->color = color;
}

void	put_line_naive(t_line *line, t_win *vars, t_data *data)
{
	int dx;
	int dy;
	int xi;
	int yi;
	int sign;

	dx = line->B->x - line->A->x;
	dy = line->B->y - line->A->y;

	sign = get_sign(dx);
	
	xi = line->A->x;
	yi = line->A->y;
	if (is_equal(line->A, line->B))
		return (my_mlx_pixel_put(data, xi, yi, line->color));
	while (xi != line->B->x)
	{
		yi = line->A->y + dy * (xi - line->A->x) / dx;
		my_mlx_pixel_put(data, xi, yi, line->color);
		xi += sign;
	}
}

void	put_line_dda(t_line *line)
{
	;
}

void	put_line_bresenheim(t_line *line)
{
	;
}

void	put_line_wu(t_line *line)
{
	;
}