#include "minirt.h"

void		set_color(t_color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = g;
}

 void		set_lamb(t_lamb *lamb, double lum, t_color *col)
 {
	lamb->lum = lum;
	lamb->col = *col;
 }

 