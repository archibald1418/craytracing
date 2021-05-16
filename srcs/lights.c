#include "minirt.h"

// Specular coefficient
#ifndef SPEC
# define SPEC 1250
#endif

// Specular light saliency
#ifndef KS    
# define KS 0.2
#endif

// Diffuse light saliency
#ifndef KD      
# define KD 1
#endif 

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

double	diffuse(t_v3d orient, t_ray l_ray)
{
	double	angle;

	angle = cos_sim(orient.dir, l_ray.dir);
	return ((angle >= 0) * angle);
}

double	specular(t_v3d orient, t_ray l_ray, t_cam cam)
{
	t_p3d	orient_to_cam;
	t_p3d	refl;
	t_p3d	tmp;
	double	angle;

	p_sub(&orient_to_cam, cam.loc, orient.loc);
	normalize(&orient_to_cam, orient_to_cam);
	scalmult(&tmp, orient.dir, 2 * dot(orient.dir, l_ray.dir));
	p_sub(&refl, tmp, l_ray.dir);
	normalize(&refl, refl);
	angle = cos_sim(refl, orient_to_cam);
	return ((angle >= 0) * pow(angle, SPEC));
}

double	phong(t_v3d orient, t_ray l_ray, t_cam cam, double base_lum)
{
	double	diff;
	double	spec;

	diff = diffuse(orient, l_ray);
	spec = specular(orient, l_ray, cam);
	return (base_lum * (spec * KS + diff * KD));
}

// int	apply_shade(t_v3d orient, t_ray s_ray, t_cam cam, t_lsrc *lsrc, int shape_color)
int apply_shade(t_light light)
{

	double curr_lum;
	int curr_color;

	curr_lum = phong(light.orient, light.s_ray, light.cam, light.lsrc.lum);
	curr_color = add_trgb(light.shape_color, get_hex(light.lsrc.col), curr_lum);
	return (curr_color);
}

int	calc_lights(int shape_color, t_v3d orient, t_rt *rt, t_cam cam)
{
	// t_ray		s_ray;
	t_bilist	*node;
	// t_lsrc		*lsrc;
	t_light		light;
	int			i;
	// int			total_color;
	double		t;
	double		mindist;

	ft_bzero(&light, sizeof(light));
	if (rt->has_lamb)
		light.total_color = add_trgb(shape_color, get_hex(rt->lamb.col), rt->lamb.lum);
	light.orient = orient;
	light.shape_color = shape_color;
	light.s_ray.loc = orient.loc;
	light.cam = cam;
	node = rt->lsrcs.head;
	while (node)
	{
		light.lsrc = *(t_lsrc*)node->content;
		light.lightdist = get_dist(light.s_ray.loc, light.lsrc.loc);
		light.s_ray.dir = p_sub(&light.s_ray.dir, light.lsrc.loc, light.s_ray.loc);
		normalize(&light.s_ray.dir, light.s_ray.dir);
		i = 0;
		mindist = light.lightdist;
		while (i < rt->shapes.top)
		{
			t = intersect_shape(rt->shapes.shapes[i], light.s_ray);
			if (!(isnan(t)) && (0.05 <= t && t < light.lightdist))
				mindist = t;
			i++;
		}
		if (isinf(mindist) || mindist >= light.lightdist)
			light.total_color = accumulate_color(light.total_color, apply_shade(light));
		node = node->next;
	}
	return (light.total_color);
}