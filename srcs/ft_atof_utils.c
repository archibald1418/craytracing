#include "minirt.h"

int	get_sign(char *str)
{
	if (*(unsigned char *)str == '+')
		return (1);
	if (*(unsigned char *)str == '-')
		return (-1);
	return (0);
}

double	get_esgn(double esgn)
{
	if (esgn >= 0)
		return (1);
	return (-1);
}
