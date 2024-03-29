#include "minirt.h"

double	get_min_pos_root(double disc, double a, double b)
{
	double	r1;
	double	r2;
	double	sqd;

	sqd = sqrt(disc);
	r1 = (-b + sqd) / (2 * a);
	r2 = (-b - sqd) / (2 * a);
	if (r1 >= 0 && r2 >= 0)
		return (fmin(r1, r2));
	if (r1 >= 0)
		return (r1);
	if (r2 >= 0)
		return (r2);
	return ((double)NAN);
}

double	sign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
}

int	t_min_max(int n, int min, int max)
{
	if (n < min)
		n = min;
	if (n > max)
		n = max;
	return (n);
}
