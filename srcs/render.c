#include "minirt.h"

ssize_t render(t_conf *conf, t_rt *rt, t_cam cam)
{
    t_v3d orient;
    int color;
    int i;
    int j;
    t_ray ray;
    int rate;

    j = 0;
    rate = 1;
    color = black;
    cam.rot = get_rotation(cam);
    while (j <= conf->res.Y - rate)
    {
        i = 0;
        while (i <= conf->res.X - rate)
        {
            init_ray(&ray, &conf->res, i, j, cam);
            color = trace_shapes(ray, rt->shapes, &orient);
            if (color != black)
                color = calc_lights(color, orient, rt, cam);
            my_mlx_pixel_put(&conf->img, i, j, color);
            i += rate;
        }
        j += rate;
    }
    return (1);
}