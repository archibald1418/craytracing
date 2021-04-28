#include "minirt.h"

// Outputs color
int trace_shapes(t_ray ray, t_shapes shapes, t_v3d *orient)
{
    int color;
    int i;
    double mindist;
    double dist;
    t_shape minshape;

    mindist = INF;
    i = 0;
    while (i < shapes.top)
    {
        dist = (double)intersect_shape(shapes.shapes[i], ray);
        if (!(isnan(dist)))
            if (dist < mindist)
            {
                mindist = dist;
                minshape = shapes.shapes[i];
            }
        i++;
    }
    if (isinf(mindist))
        return (black);
    scalmult(&orient->loc, ray.dir, mindist);
    p_add(&orient->loc, ray.loc, orient->loc);
    calc_shape_normal(orient, minshape);
    return (convert_color(get_shape_color(minshape)));
}