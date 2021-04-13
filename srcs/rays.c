#include "minirt.h"

#define INF	(double)INFINITY



// t_v3d	*get_nearest(t_ray *ray, t_shapes *shapes)
// {
// 	t_v3d tmp;

// 	init_v3d(&tmp, INF, INF, INF);	

// 	return (&tmp);
// }

void	init_ray(t_ray *ray, t_res *res, int px, int py, double fov) // TODO: pass t_res as resolution and t_point as pixel point
{
	double aspect_ratio;
	double screenx;
	double screeny;
	double camx;
	double camy;

	aspect_ratio = (double)((double)res->X / (double)res->Y); // TODO: should be parsed and passed on to here
	screenx = 2.0 * (((double)px + 0.5) / (double)res->X) - 1;
	screeny = 1.0 - 2 * (((double)py + 0.5) / (double)res->Y);
	camx = screenx * atan(fov/2) * aspect_ratio; // FIXME: multiply by screeny if aspect_ratio > 1 (to unsquish pixels vertically)
	camy = screeny * atan(fov/2);

	// Ray construction
	ray->loc = (t_p3d){0, 0, 0}; // TODO: pass actual camera origin to here. Zeros are default origin
	ray->dir = (t_p3d){0, 0, 0};
	p_sub(&ray->dir, (t_p3d){camx, camy, 1.0}, ray->loc); // z = -1 => camera is unit away from the canvas (in camera coords)
	// normalize direction
	normalize(&ray->dir, ray->dir);

	// TODO: cam to world matrix for rotation and translation
}

