#include "minirt.h"

// Specular coefficient
#ifndef SPEC
# define SPEC 1250
#endif

// Specular light saliency
#ifndef KS      
# define KS     0.2
#endif

// Diffuse light saliency
#ifndef KD         
# define KD     1
#endif 

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

double diffuse(t_v3d orient, t_ray l_ray)
{
    double angle;

    angle = cos_sim(orient.dir, l_ray.dir);
    return ((angle >= 0) * angle);

}

double  specular(t_v3d orient, t_ray l_ray, t_cam cam)
{
    t_p3d orient_to_cam;
    t_p3d refl;
    t_p3d tmp;
    double angle;

    // Vector V
    p_sub(&orient_to_cam, cam.loc, orient.loc);
    normalize(&orient_to_cam, orient_to_cam);

    // Vector R
    scalmult(&tmp, orient.dir, 2 * dot(orient.dir, l_ray.dir));
    p_sub(&refl, tmp, l_ray.dir);
    normalize(&refl, refl);

    angle = cos_sim(refl, orient_to_cam);

    return ((angle >= 0) * pow(angle, SPEC));
}

double phong(t_v3d orient, t_ray l_ray, t_cam cam, double base_lum)
{
    double diff;
    double spec;

    diff = diffuse(orient, l_ray);
    spec = specular(orient, l_ray, cam);
    return (base_lum * (spec * KS + diff * KD));
}

int calc_lights(int shape_color, t_v3d orient, t_rt *rt, t_cam cam)
{
    t_ray   s_ray; 
    t_bilist  *node;
    t_lsrc  *lsrc;
    int i;
    int total_color;
    double t;
    double lightdist;
    int curr_color;
    double mindist;
    double total_lum;

    // Add ambient;
    total_color = total_lum = 0;
    if (rt->has_lamb)
    {
        total_color = add_trgb(shape_color, get_hex(rt->lamb.col));
        total_lum = rt->lamb.lum;
    }

    // Get shadow ray location (an already biased orient)
    s_ray.loc = orient.loc;
    node = rt->lsrcs.head;
    while (node)
    {   
        lsrc = (t_lsrc*)node->content;
        lightdist = get_dist(s_ray.loc, lsrc->loc);

        /* Get phit to light vector direction */
        s_ray.dir = p_sub(&s_ray.dir, lsrc->loc, s_ray.loc);
        normalize(&s_ray.dir, s_ray.dir);

        // Check for intersections
        i = 0;
        mindist = lightdist;
        while (i < rt->shapes.top)
        {
            t = intersect_shape(rt->shapes.shapes[i], s_ray);
            if (!(isnan(t)) && (0.05 <= t && t < lightdist))
                mindist = t;
            i++;
        }

        // If no intersection in the light's way, light it
        if (isinf(mindist) || mindist >= lightdist)
        {
            curr_color = add_trgb(shape_color, get_hex(lsrc->col));
            total_color = accumulate_color(total_color, curr_color);
            total_lum += phong(orient, s_ray, cam, lsrc->lum);
        }
        node = node->next;
    }
    return (set_lum(total_color, fmin(total_lum, 1)));
}