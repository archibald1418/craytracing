#include "minirt.h"



int calc_lights(int shape_color, t_v3d orient, t_rt *rt)
{
    t_ray   s_ray; 
    t_bilist  *node;
    t_lsrc  *lsrc;
    int i;
    double intens;
    double angle;
    int color;

    s_ray.loc = orient.loc;
    node = rt->lsrcs.head;
    intens = rt->lamb.lum;
    color = shape_color;
    if (get_hex(rt->lamb.col) > 0 || rt->lamb.lum > 0)
        color = add_trgb(shape_color, get_hex(rt->lamb.col)); //add ambient;
    while (node)
    {   
        lsrc = (t_lsrc*)node->content;
        p_sub(&s_ray.dir, lsrc->loc, orient.loc);
        // normalize(&s_ray.dir, s_ray.dir);
        i = 0;
        while (i < rt->shapes.top)
        {
            if (!(isnan(intersect_shape(rt->shapes.shapes[i], s_ray))))
                break;
            i++;
        }
        // if (i != 1)
        // printf("top = %d\n", rt->shapes.top);
        if (i == rt->shapes.top)
        {
            angle = cos_sim(orient.dir, s_ray.dir);
            if (!(isnan(angle)) && angle >= 0)
                intens += angle;
            color = add_trgb(color, get_hex(lsrc->col));
        }
        node = node->next;
    }
    return (set_lum(color, fmin(intens, 1)));
}