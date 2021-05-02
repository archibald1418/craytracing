#include "minirt.h"

//TODO: acculumate color function

int     accumulate_color(int prev, int curr)
{
    int rnew;
    int gnew;
    int bnew;

    rnew = fmin(get_r(prev) + get_r(curr), 255);
    gnew = fmin(get_g(prev) + get_r(curr), 255);
    bnew = fmin(get_b(prev) + get_b(curr), 255);

    return (create_trgb(0, rnew, gnew, bnew));

}

int calc_lights(int shape_color, t_v3d orient, t_rt *rt)
{
    t_ray   s_ray; 
    t_bilist  *node;
    t_lsrc  *lsrc;
    int i;
    double angle;
    int total_color;
    int curr_color;

    s_ray.loc = orient.loc;
    node = rt->lsrcs.head;
    total_color = 0;
    total_color = set_lum(add_trgb(shape_color, get_hex(rt->lamb.col)), rt->lamb.lum); //add ambient;
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
            curr_color = set_lum(add_trgb(shape_color, get_hex(lsrc->col)), lsrc->lum * angle * (angle >= 0));
            total_color = accumulate_color(total_color, curr_color);
        }
        node = node->next;
    }
    return (total_color);
}