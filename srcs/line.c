#include "minirt.h"

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

	dx = line->B->x - line->A->x;
	dy = line->B->y - line->A->y;
	
	xi = line->A->x;
	// TODO: do backward direction (xi--)
	while (xi < line->B->x)
	{
		yi = line->A->y + dy * (xi - line->A->x) / dx;
		my_mlx_pixel_put(data, xi, yi, line->color);
		xi++;
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