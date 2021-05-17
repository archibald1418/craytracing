#include "minirt.h"

double	det2(t_p2d v, t_p2d u)
{
	return (v.x * u.y - u.x * v.y);
}

int	is_not_zero(t_p3d vec)
{
	return (vec.x || vec.y || vec.z);
}
