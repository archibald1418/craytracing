#include "minirt.h"

ssize_t render(t_conf *conf, t_rt *rt)
{
    t_p3d phit;
    int color;
    int i;
    int j;
    t_ray ray;

    i = 0;
    j = 0;
    color = black;
    t_cam cam = (t_cam){(t_p3d){0, 0, 0}, (t_p3d){1, 1, 1}, 60};
    while (j < conf->res.Y)
    {
        while (i < conf->res.X)
        {
            init_ray(&ray, &conf->res, i, j, cam);
            color = trace_shapes(ray, rt->shapes);
            my_mlx_pixel_put(&conf->img, i, j, color);
        }
    }
    return (1);
}