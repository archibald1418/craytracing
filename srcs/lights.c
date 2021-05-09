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
    int total_color;
    double t;
    double lightdist;
    int curr_color;
    // double root;
    // double mindist;
    // t_shape minshape;
    // double angle;

    // Add ambient;
    total_color = set_lum(add_trgb(shape_color, get_hex(rt->lamb.col)), rt->lamb.lum);

    // Get shadow ray location (an already biased orient)
    s_ray.loc = orient.loc;
    node = rt->lsrcs.head;
    t = NAN;
    while (node)
    {   
        lsrc = (t_lsrc*)node->content;
        lightdist = get_dist(s_ray.loc, lsrc->loc);


        // Get phit to light vector direction
        s_ray.dir = p_sub(&s_ray.dir, lsrc->loc, orient.loc);
        normalize(&s_ray.dir, s_ray.dir);

        // Check for intersections
        i = 0;
        while (i < rt->shapes.top)
        {
            t = intersect_shape(rt->shapes.shapes[i], s_ray);
            if (!(isnan(t)))
                break;
            i++;
        }
        
        // If no intersection in the light's way, light it
        if (isnan(t) || t >= lightdist)
        {
            // todo: add light distance multpiplier
            curr_color = set_lum(add_trgb(shape_color, get_hex(lsrc->col)), lsrc->lum); 
            total_color = accumulate_color(total_color, curr_color);
        }
        node = node->next;
    }
    return (total_color);
}