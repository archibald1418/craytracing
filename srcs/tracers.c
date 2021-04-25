#include "minirt.h"

int     convert_color(t_color color)
{
    return (create_trgb(0, color.r, color.b, color.r));
}


t_color get_shape_color(t_shape shape)
{
    if (ft_strcmp(shape.label, SP))
        return ((t_sp *)shape.shape)->color;
    if (ft_strcmp(shape.label, SQ))
        return (((t_sq *)shape.shape)->color);
    if (ft_strcmp(shape.label, PL))
        return (((t_pl *)shape.shape)->color);
    if (ft_strcmp(shape.label, CY))
        return (((t_cy *)shape.shape)->color);
    if (ft_strcmp(shape.label, TR))
        return (((t_tr *)shape.shape)->color);
}
// Outputs color
int trace_shapes(t_ray ray, t_shapes shapes)
{
    int color;
    int i;
    double mindist;
    double dist;
    t_p3d  phit;
    t_shape minshape;

    mindist = INF;
    i = 0;
    while (i < shapes.top)
    {
        dist = intersect_shape(shapes.shapes[i], ray);
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