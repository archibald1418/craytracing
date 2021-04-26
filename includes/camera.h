#ifndef CAMERA_H
# define CAMERA_H

# include "vectors.h"

typedef struct	s_cam
{
	t_p3d	loc;
	t_p3d	dir;
	int		fov;
}				t_cam;

void	init_camera(t_cam *cam, t_p3d loc, t_p3d dir, int fov);
void	init_ray(t_ray *ray, t_res *res, int px, int py, t_cam cam);
#endif