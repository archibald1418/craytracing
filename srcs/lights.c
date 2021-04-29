#include "minirt.h"



int calc_lights(int shape_color, t_v3d orient, t_rt *rt)
{
    t_ray   s_ray; 
    t_bilist  *node;
    t_lsrc  *lsrc;
    int i;
    double intens;
    double angle;

    s_ray.loc = orient.loc;
    // amb = set_lum(add_trgb(shape_color, convert_color(rt->lamb.col)), rt->lamb.lum);
    node = rt->lsrcs.head;
    intens = rt->lamb.lum;
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
            if (!(isnan(angle)) && angle > 0)
                intens += angle;
            // color += set_lum(convert_color(lsrc->col), lsrc->lum);
        }
        node = node->next;
    }
    // return (amb);


    // Shadows

    // Diffuse
    return (set_lum(shape_color, fmin(intens, 1)));
}