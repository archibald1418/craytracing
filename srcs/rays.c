#include "minirt.h"


// t_v3d	*get_nearest(t_ray *ray, t_shapes *shapes)
// {
// 	t_v3d tmp;

// 	init_v3d(&tmp, INF, INF, INF);	

// 	return (&tmp);
// }

void	init_ray(t_v3d *ray, t_res *res, int px, int py, t_cam cam) // TODO: pass t_res as resolution and t_point as pixel point
{
	double aspect_ratio;
	double screenx;
	double screeny;
	double viewx;
	double viewy;
	double viewz;

	aspect_ratio = (double)((double)res->X * pow(res->Y, -1)); // TODO: should be parsed and passed on to here
	screenx = 2.0 * (((double)px + 0.5) * (double)pow(res->X, -1)) - 1;
	screeny = 1.0 - 2 * (((double)py + 0.5) * (double)pow(res->Y, -1));
	viewx = screenx * tan(cam.fov/2 * M_PI / 180);
	viewy = screeny * tan(cam.fov/2 * M_PI / 180);

	// tan vs atan - tan makes closer

	if (res->X >= res->Y)
		viewy *= pow(aspect_ratio, -1);
	else
		viewx *= aspect_ratio;
	// FIXME: multiply by screeny if aspect_ratio > 1 (to unsquish pixels vertically)

	viewz = 1;
	
	// Ray construction
	ray->loc.x = cam.loc.x;
	ray->loc.y = cam.loc.y;
	ray->loc.z = cam.loc.z;
	p_sub(&ray->dir, (t_p3d){viewx, viewy, cam.loc.z + 1}, ray->loc); // z = -1 => camera is unit away from the canvas (in camera coords)
	// normalize direction
	
	normalize(&ray->dir, ray->dir);
	// if ((camx == res->X / 2) && (camy == res->Y / 2))
	// 	printf("RAYDIR -> (%f,%f,%f)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	// if (camx == res->X - 1 && camy == res->Y - 1)
	// 	printf("RAYDIR -> (%f,%f,%f)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	// if (camx >= 0 &&  camx <= 0.1 && camy >= 0 && camy <= 0.1)
	// 	printf("RAYDIR -> (%f,%f,%f)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	// if (camx == 0 && camy == res->Y - 1)
	// 	printf("RAYDIR -> (%f,%f,%f)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	// if (camx == res->X - 1 && camy == 0)
	// 	printf("RAYDIR -> (%f,%f,%f)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	
	// TODO: cam to world matrix for rotation and translation
}

