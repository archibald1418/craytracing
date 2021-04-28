#include "minirt.h"

ssize_t render(t_conf *conf, t_rt *rt)
{
    t_v3d orient;
    int color;
    int i;
    int j;
    t_ray ray;

    j = 0;
    color = black;
    t_cam cam = (t_cam){(t_p3d){0, 0, 0}, (t_p3d){0, 0, 0}, 100};
    while (j < conf->res.Y)
    {
        i = 0;
        while (i < conf->res.X)
        {
            init_ray(&ray, &conf->res, i, j, cam);
            color = trace_shapes(ray, rt->shapes, &orient);
            if (color != black)
                color = calc_lights(color, orient, rt);
            my_mlx_pixel_put(&conf->img, i, j, color);
            i++;
        }
        j++;
    }
    return (1);
}