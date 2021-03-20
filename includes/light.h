#ifndef LIGHT_H
# define LIGHT_H

# include "colors.h"
# include "vectors.h"

typedef struct	s_lamb
{
	double	lum;
	t_color	*col;
}				t_lamb;

typedef struct	s_lsrc
{
	double	lum;
	t_color	*col;
	t_v3d	*p;
}				t_lsrc;

#endif