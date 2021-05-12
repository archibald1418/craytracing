#include "minirt.h"


t_p3d   get_new_point(t_p3d loc, t_p3d dir, double t)
{
    t_p3d p;
    scalmult(&p, dir, t);
    p_add(&p, p, loc);
    return (p);
}
// Outputs color
int trace_shapes(t_ray ray, t_shapes shapes, t_v3d *orient)
{
    int i;
    double mindist;
    double dist;
    t_shape minshape;
    t_p3d tmp;

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
    // Get point normal

    scalmult(&orient->loc, ray.dir, mindist);
    p_add(&orient->loc, ray.loc, orient->loc);

    calc_point_normal(orient, minshape, ray, mindist);

    scalmult(&tmp, orient->dir, 0.05);
    p_add(&orient->loc, tmp, orient->loc);
    // Get exact point of intersection
    // orient->loc = get_new_point(orient->loc, orient->dir, mindist);

    // // Nudge point away from shape to avoid self-intersect
    // orient->loc = get_new_point(orient->loc, orient->dir, 0.0001);

    return (get_hex(get_shape_color(minshape)));
}