#include "minirt.h"

t_p3d	get_new_point(t_p3d loc, t_p3d dir, double t)
{
	t_p3d	p;

	scalmult(&p, dir, t);
	p_add(&p, p, loc);
	return (p);
}

static void	treat_mins(double *mindist, double *dist, \
					t_shape *minshape, t_shape *shape)
{
	if (*dist < *mindist)
	{
		*mindist = *dist;
		*minshape = *shape;
	}
}

int	trace_shapes(t_ray ray, t_shapes shapes, t_v3d *orient)
{
	int		i;
	double	mindist;
	double	dist;
	t_shape	minshape;
	t_p3d	tmp;

	mindist = INF;
	i = 0;
	while (i < shapes.top)
	{
		dist = (double)intersect_shape(shapes.shapes[i], ray);
		if (!(isnan(dist)))
			treat_mins(&mindist, &dist, &minshape, &shapes.shapes[i]);
		i++;
	}
	if (isinf(mindist))
		return (black);
	scalmult(&orient->loc, ray.dir, mindist);
	p_add(&orient->loc, ray.loc, orient->loc);
	calc_point_normal(orient, minshape, ray);
	scalmult(&tmp, orient->dir, 0.05);
	p_add(&orient->loc, tmp, orient->loc);
	return (get_hex(get_shape_color(minshape)));
}
