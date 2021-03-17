#ifndef CAMERA_H
# define CAMERA_H

# include "vectors.h"

typedef struct	s_cam
{
	t_v3d	vp;
	t_v3d	dir;
	int		fov;
}				t_cam;

#endif