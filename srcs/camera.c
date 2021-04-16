#include "minirt.h"

void	init_camera(t_cam *cam, t_p3d loc, t_p3d dir, int fov)
{
    cam->loc = loc;
    cam->loc = dir;
    cam->fov = fov;
}

