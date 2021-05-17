#include "minirt.h"

void	set_color(t_color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

void	set_lamb(t_lamb *lamb, double lum, t_color *col)
{
	lamb->lum = lum;
	lamb->col.r = col->r;
	lamb->col.g = col->g;
	lamb->col.b = col->b;
}

void	set_lsrc(t_lsrc *lsrc, double lum, t_color col, t_p3d p)
{
	lsrc->lum = lum;
	lsrc->col.r = col.r;
	lsrc->col.g = col.g;
	lsrc->col.b = col.b;
	lsrc->loc.x = p.x;
	lsrc->loc.x = p.y;
	lsrc->loc.x = p.z;
}
