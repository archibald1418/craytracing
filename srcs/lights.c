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

// int diffuse(t_ray l_ray, t_v3d orient, int shape_color)
// {
//     double light_dot_shape;
//     double angle_cos;

//     light_dot_shape = dot(l_ray.dir, orient.dir);
    

// }

int calc_lights(int shape_color, t_v3d orient, t_rt *rt)
{
    t_ray   s_ray; 
    t_bilist  *node;
    t_lsrc  *lsrc;
    int i;
    int total_color;
    int curr_color;
    double root;
    double shape_dot_light;
    // double mindist;
    // t_shape minshape;

    node = rt->lsrcs.head;
    total_color = set_lum(add_trgb(shape_color, get_hex(rt->lamb.col)), rt->lamb.lum); //add ambient;
    // mindist = INF;
    while (node)
    {   
        lsrc = (t_lsrc*)node->content;
        s_ray.loc = orient.loc;
        p_sub(&s_ray.dir, lsrc->loc, orient.loc);
        // normalize(&s_ray.dir, s_ray.dir); // Should not be normalised

        // Check for intersections
        i = 0;
        while (i < rt->shapes.top)
        {
            if (!(isnan(root = intersect_shape(rt->shapes.shapes[i], s_ray))) && (0.01 <= root && root <= 1))
            {
                node = node->next;
                continue;
            }
            i++;
        }
        shape_dot_light = dot(orient.dir, s_ray.dir);
        curr_color = set_lum(add_trgb(shape_color, get_hex(lsrc->col)), lsrc->lum * cos_sim(orient.dir, s_ray.dir) * (shape_dot_light > 0));
        total_color = accumulate_color(total_color, curr_color);
        node = node->next;
    }
    return (total_color);
}