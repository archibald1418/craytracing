#include "minirt.h"

// Outputs color
int trace_shapes(t_ray ray, t_shapes shapes)
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
    return (convert_color(get_shape_color(minshape)));
}