#include "minirt.h"

static double	ssign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
}
static double	calc_mantissa(int e, double num, int esign)
{
	double mult;

	mult = (esign >= 0) ? 10.0 : 0.1;
	while (e != 0)
	{
		num *= mult;
		e -= esign;
	}
	return (num);
}

static double		iter_digits(char **str, int sgn, int is_e)
{
	double num;

	num = 0.0;
	*str += (sgn != 0);
	while (ft_isdigit((int)**str))
	{
		num = num * 10.0 + (double)((int)**str - '0');
		(*str)++;
	}
	if (sgn < 0 && !is_e)
		return (num * -1.0);
	return (num);
}

static int		get_sign(char *str)
{
	if (*(unsigned char *)str == '+')
		return (1);
	if (*(unsigned char *)str == '-')
		return (-1);
	return (0);
}


double	ft_atof(char *s)
{
	int		e;
	double	num;
	int		sgn;
	int		i;

	e = 0;
	i = 0;
	sgn = get_sign(s);
	num = iter_digits(&s, sgn, 0);
	if (*s == '.')
		while (ft_isdigit(*++s))
		{
			num = num * 10.0 + (double)((int)((*s) - '0'));
			e -= 1;
		}
	if (*s == 'e' || *s == 'E')
	{
		sgn = get_sign(++s);
		i = (double)(iter_digits(&s, sgn, 1));
		sgn = (sgn >= 0) ? 1 : -1;
		e += (i * sgn);
	}
	if (*s != '\0')
		return ((double)NAN);
	return (calc_mantissa(e, num, ssign(e)));
}