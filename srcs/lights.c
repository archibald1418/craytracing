#include "minirt.h"

int calc_lights(int shape_color, t_v3d orient, t_rt *rt)
{
    int     amb;
    int     color;
    t_ray   s_ray; 
    t_bilist  *node;
    t_lsrc  *lsrc;
    int i;

    s_ray.loc = orient.loc;
    amb = set_lum(add_trgb(shape_color, convert_color(rt->lamb.col)), rt->lamb.lum);
    color = amb;
    node = rt->lsrcs.head;
    while (node)
    {   
        lsrc = (t_lsrc*)node->content;
        p_sub(&s_ray.dir, orient.loc, lsrc->loc);
        normalize(&s_ray.dir, s_ray.dir);
        i = 0;
        while (i < rt->shapes.top)
        {
            if (!(isnan(intersect_shape(rt->shapes.shapes[i], s_ray))))
                break;
            i++;
        }
        if (i == rt->shapes.top)
            color = set_lum(add_trgb(shape_color, convert_color(lsrc->col)), lsrc->lum);
        node = node->next;
    }
    // return (amb);


    // Shadows

    // Diffuse
    return (color);
}