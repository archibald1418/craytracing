#include "minirt.h"

static double	get_sign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
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
	double xi;
	double yi;
	int signx;
	int signy;
	int step;
	int i;
	int tmp;
	// bool endFound;
	// endFound = false;

	i = 0;
	

	dx = (double)(line->B->x - line->A->x);
	dy = (double)(line->B->y - line->A->y);
	
	signx = get_sign(dx);
	signy = get_sign(dy);
	xi = (double)line->A->x;
	yi = (double)line->A->y;
	if (is_equal(line->A, line->B))
		return (my_mlx_pixel_put(conf->img, xi, yi, line->color));
	step = (fabs(dx) >= fabs(dy)) ? fabs(dx) : fabs(dy);
	
	// Traverse axes with dx/dy normalized on step
	dx /= step; 
	dy /= step;
	/*
	TODO: endpoint is either known (line drawing) or calculated (start + rayDir * rayLen):
	rayDir
	*/
	// FIXME: WORKS ONLY WITH POSITIVE SLOPES (TODO: ADD SIGN MULTIPLIER)

	while (i < step && \
	0.0 <= xi && xi <= (double)conf->res->X && \
	0.0 <= yi && yi <= (double)conf->res->Y)
	{
		if ((tmp = my_mlx_pixel_get(conf->img, xi, yi)) == black)
			tmp = set_lum(line->color, 1.0);
		my_mlx_pixel_put(conf->img, (int)xi, (int)yi, add_trgb(line->color, tmp));
		xi += dx;
		yi += dy * signy;
		i += 1;
	}
}

void	put_line_bresenham(t_line *line, t_conf *conf)
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

void	translate_line(t_line *line, t_grad *g, t_conf *conf, void (*put_line)(t_line *, t_conf *))
{
	t_line tmp[sizeof(t_line)];

	copy_line(tmp, line);
	move_line(tmp, (t_point *)g);
	put_line((t_line *)tmp, conf);
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