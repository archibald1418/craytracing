#include "minirt.h"

void    get_sp_normal(t_v3d *orient, t_sp *sp)
{
    p_sub(&orient->dir, orient->loc, sp->c);
}

void    calc_shape_normal(t_v3d *orient, t_shape shape)
{
     if (ft_strcmp(shape.label, SP) == 0)
        return (get_sp_normal(orient, (t_sp *)shape.shape));

    //TODO: 
	// if (ft_strcmp(shape.label, SQ))
    //     return(get_sp_normal((t_sq *)shape.shape, ray));
    // if (ft_strcmp(shape.label, PL))
    //     return(get_sp_normal((t_pl *)shape.shape, ray));
    // if (ft_strcmp(shape.label, CY))
    //     return(get_sp_normal((t_cy *)shape.shape, ray));
    // if (ft_strcmp(shape.label, TR))
    //     return(get_sp_normal((t_tr *)shape.shape, ray));
}