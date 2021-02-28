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
	dprintf(1, "x0=%d --> xn=%d\n", line->A->x, line->B->x); 
	dprintf(1, "y0=%d --> xy=%d\n", line->A->y, line->B->y);
	while (xi < line->B->x && yi < line->B->y)
	{
		yi = line->A->y + dy * (xi - line->A->x) / dx; 
		dprintf(1, "xi=%3d ; yi=%3d; dxi = %3d; dy/dx=%.2f\n", xi, yi, xi - line->A->x, (double)dy/(double)dx);
		my_mlx_pixel_put(data, xi, yi, line->color);
		xi += sign;
	}
	// dprintf(1, "xi=%3d ; yi=%3d; dxi = %3d; dy/dx=%.2f\n", xi, yi, xi - line->A->x, (double)dy/(double)dx);
	// my_mlx_pixel_put(data, line->B->x, line->B->y, line->color);
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