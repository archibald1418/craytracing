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

void	put_line_naive(t_line *line, t_conf *conf)
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
		return (my_mlx_pixel_put(conf->img, xi, yi, line->color));
	if (dx != 0)
		while (xi != line->B->x)
		{
			yi = line->A->y + dy * (xi - line->A->x) / dx;
			my_mlx_pixel_put(conf->img, xi, yi, line->color);
			xi += sign;
		}
	else 
	{
		sign = get_sign(dy);
		while (yi != line->B->y)
			my_mlx_pixel_put(conf->img, xi, yi += sign, line->color);
	}
	
}

void	put_line_dda(t_line *line, t_conf *conf)
{
	double dx;
	double dy;
	int xi;
	int yi;
	int sign;
	int step;


	dx = (double)(line->B->x - line->A->x);
	dy = (double)(line->B->y - line->A->y);
	
	xi = line->A->x;
	yi = line->A->y;
	if (is_equal(line->A, line->B))
		return (my_mlx_pixel_put(conf->img, xi, yi, line->color));
	step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);
	dx /= step;
	dy /= step;
	while (xi != line->B->x)
	{

		yi = line->A->y + dy * (xi - line->A->x) / dx;
		my_mlx_pixel_put(conf->img, xi, yi, line->color);
		xi += sign;
	}
}

void	put_line_bresenheim(t_line *line, t_conf *conf)
{
	;
}

void	put_line_wu(t_line *line, t_conf *conf)
{
	;
}

t_line *copy_line(t_line *dst, t_line* src)
{
	return ((t_line *)ft_memcpy(dst, src, sizeof(t_line)));
}

void	move_line(t_line *line, t_point *offset)
{
	move_point(line->A, offset);
	move_point(line->B, offset);
}

void	translate_line(t_line *line, t_grad *g, t_conf *conf)
{
	t_line tmp[sizeof(t_line)];

	copy_line(tmp, line);
	move_line(tmp, (t_point *)g);
	put_line_naive((t_line *)tmp, conf);
}

int		are_parallel(t_line *a, t_line *b)
{
	double dera;
	double derb;
	//double thresh;
	// FLOATS MAY BEHAVE BADLY

	dera = calc_der(a);
	derb = calc_der(b);

	return (0);
	/* FIXME: No, equal ders only tells if lines are copies 
	Lines of different length also can be parallel!!!*/
}