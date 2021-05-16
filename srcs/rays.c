#include "minirt.h"


// t_v3d	*get_nearest(t_ray *ray, t_shapes *shapes)
// {
// 	t_v3d tmp;

// 	init_v3d(&tmp, INF, INF, INF);	

// 	return (&tmp);
// }

void	init_ray(t_v3d *ray, t_res *res, int px, int py, t_cam cam)
{
	double aspect_ratio;
	double screenx;
	double screeny;
	double viewx;
	double viewy;
	double viewz;

	aspect_ratio = (double)((double)res->X * pow(res->Y, -1));
	screenx = 2.0 * (((double)px + 0.5) * (double)pow(res->X, -1)) - 1;
	screeny = 1.0 - 2 * (((double)py + 0.5) * (double)pow(res->Y, -1));
	viewx = screenx * tan(cam.fov/2 * M_PI / 180);
	viewy = screeny * tan(cam.fov/2 * M_PI / 180);

	if (res->X >= res->Y)
		viewy *= pow(aspect_ratio, -1);
	else
		viewx *= aspect_ratio;
	
	ray->loc.x = cam.loc.x;
	ray->loc.y = cam.loc.y;
	ray->loc.z = cam.loc.z;
	viewz = cam.loc.z + 1;

	p_sub(&ray->dir, (t_p3d){viewx, viewy, viewz}, ray->loc);
	normalize(&ray->dir, ray->dir);
	ray->dir = rot_ray(cam, *ray);
}