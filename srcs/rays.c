#include "minirt.h"

void	init_ray(t_v3d *ray, t_res *res, t_point p, t_cam cam)
{
	double	aspect_ratio;
	double	screenx;
	double	screeny;
	t_p3d	view;

	aspect_ratio = (double)((double)res->X * pow(res->Y, -1));
	screenx = 2.0 * (((double)p.x + 0.5) * (double)pow(res->X, -1)) - 1;
	screeny = 1.0 - 2 * (((double)p.y + 0.5) * (double)pow(res->Y, -1));
	view.x = screenx * tan(cam.fov / 2 * M_PI / 180);
	view.y = screeny * tan(cam.fov / 2 * M_PI / 180);
	if (res->X >= res->Y)
		view.y *= pow(aspect_ratio, -1);
	else
		view.x *= aspect_ratio;
	ray->loc.x = cam.loc.x;
	ray->loc.y = cam.loc.y;
	ray->loc.z = cam.loc.z;
	view.z = cam.loc.z + 1;
	p_sub(&ray->dir, (t_p3d){view.x, view.y, view.z}, ray->loc);
	normalize(&ray->dir, ray->dir);
	ray->dir = rot_ray(cam, *ray);
}
