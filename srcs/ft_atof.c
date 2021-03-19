#include "minirt.h"

static double	calc_mantissa(int e, double num, int esign)
{
	double mult;

	mult = (esign > 0) ? 10.0 : 0.1;
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
	if ((**str == '.' && is_e) || (is_e && **str != '\0'))
		return (EPSILON); // FIXME: WHAT VALUE TO RETURN???
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

	sgn = get_sign(s);
	e = 0;
	i = 0;
	if ((num = iter_digits(&s, sgn, 0)) == EPSILON)
		return (EPSILON);
	if (*s++ == '.')
		while (*s && ft_isdigit(*s))
		{
			num = num * 10.0 + (double)((int)((*s) - '0'));
			e -= 1;
			s++;
		}
	if (*s == 'e' || *s == 'E')
	{
		sgn = get_sign(++s);
		if ((i = (double)(iter_digits(&s, sgn, 1))) == EPSILON)
			return (EPSILON);
		sgn = (sgn >= 0) ? 1 : -1;
		e += (i * sgn);
	}
	// if (!ft_isdigit(*s) || *s != '\0')
	// 	return (nan(""));
	return (calc_mantissa(e, num, sign(e)));
}