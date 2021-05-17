#include "minirt.h"

double	dot_alpha(t_p3d v, double angle)
{
	return (get_len(v) * cos(angle));
}

double	cos_sim(t_p3d v, t_p3d u)
{
	double	len_v;

	len_v = get_len(v);
	if (len_v == 0)
	{
		handle_errors("ZERO VECTOR CAN'T BE MEASURED!\n");
		return ((double)NAN);
	}
	return (dot(v, u) * pow(len_v * get_len(u), -1));
}
