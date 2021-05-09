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
    calc_point_normal(orient, minshape, ray);

    // Get exact point of intersection
    orient->loc = get_new_point(orient->loc, orient->dir, mindist);

    // Nudge point away from shape to avoid self-intersect
    orient->loc = get_new_point(orient->loc, orient->dir, 0.01);

    // scalmult(&orient->loc, ray.dir, mindist);
    // p_add(&orient->loc, ray.loc, orient->loc);

    
    // scalmult(&tmp, orient->dir, 0.001);
    // p_add(&orient->loc, tmp, orient->loc);
    return (get_hex(get_shape_color(minshape)));
}