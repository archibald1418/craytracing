#include "minirt.h"

int calc_lights(int shape_color, t_v3d orient, t_rt *rt)
{
    int amb;

    amb = set_lum(add_trgb(shape_color, convert_color(rt->lamb.col)), rt->lamb.lum);
    return (amb);

    // Shadows

    // Diffuse
}