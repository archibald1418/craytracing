#include "minirt.h"

void	init_camera(t_cam *cam, t_p3d loc, t_p3d dir, int fov)
{
    cam->loc.x = loc.x;
    cam->loc.y = loc.y;
    cam->loc.z = loc.z;

    // cam->loc = loc;
    // cam->dir = dir;

    cam->dir.x = dir.x;
    cam->dir.y = dir.y;
    cam->dir.z = dir.z;
    
    cam->fov = fov;
}

