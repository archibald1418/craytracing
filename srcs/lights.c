#include "minirt.h"

int	accumulate_color(int prev, int curr)
{
	int	rnew;
	int	gnew;
	int	bnew;

	rnew = fmin(get_r(prev) + get_r(curr), 255);
	gnew = fmin(get_g(prev) + get_g(curr), 255);
	bnew = fmin(get_b(prev) + get_b(curr), 255);
	return (create_trgb(0, rnew, gnew, bnew));
}

int	apply_shade(t_light light)
{
	double	curr_lum;
	int		curr_color;

	curr_lum = phong(light.orient, light.s_ray, light.cam, light.lsrc.lum);
	curr_color = add_trgb(light.shape_color, get_hex(light.lsrc.col), curr_lum);
	return (curr_color);
}

t_light	set_light(t_rt *rt, t_v3d orient, t_cam cam, int shape_color)
{
	t_light	light;

	ft_bzero(&light, sizeof(light));
	if (rt->has_lamb)
		light.total_color = add_trgb(shape_color, \
		get_hex(rt->lamb.col), \
		rt->lamb.lum);
	light.orient = orient;
	light.shape_color = shape_color;
	light.s_ray.loc = orient.loc;
	light.cam = cam;
	return (light);
}

static double	iter_shapes(t_rt *rt, t_light *light)
{
	double	mindist;
	double	t;
	int		i;

	i = 0;
	mindist = light->lightdist;
	while (i < rt->shapes.top)
	{
		t = intersect_shape(rt->shapes.shapes[i], light->s_ray);
		if (!(isnan(t)) && (0.05 <= t && t < light->lightdist))
			mindist = t;
		i++;
	}	
	return (mindist);
}

int	calc_lights(int shape_color, t_v3d orient, t_rt *rt, t_cam cam)
{
	t_bilist	*node;
	t_light		light;
	double		mindist;

	light = set_light(rt, orient, cam, shape_color);
	node = rt->lsrcs.head;
	while (node)
	{
		light.lsrc = *(t_lsrc *)node->content;
		light.lightdist = get_dist(light.s_ray.loc, light.lsrc.loc);
		light.s_ray.dir = p_sub(&light.s_ray.dir, \
		light.lsrc.loc, \
		light.s_ray.loc);
		normalize(&light.s_ray.dir, light.s_ray.dir);
		mindist = light.lightdist;
		mindist = iter_shapes(rt, &light);
		if (isinf(mindist) || mindist >= light.lightdist)
			light.total_color = accumulate_color(light.total_color, \
			apply_shade(light));
		node = node->next;
	}
	return (light.total_color);
}
