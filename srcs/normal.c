#include "minirt.h"

#define IN_RANGE(x, a, b) ()

void	init_norm(t_norm3d *norm, double x, double y, double z)
{
	if (isnormal(x) && \
		isnormal(y) && \
		isnormal (z)
		)
	{
		norm->x = x;
		norm->y = y;
		norm->z = z;
	}
	else
	{ 
		norm->x = 0;
		norm->y = 0;
		norm->z = 0;
		dprintf(1, "NOT A NORMAL: SET TO 0\n");
	}
}