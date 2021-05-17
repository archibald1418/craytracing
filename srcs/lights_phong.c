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
