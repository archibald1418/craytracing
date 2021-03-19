#include "parser.c"

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

static char		*iter_spaces(char *c)
{
	while (*c != '\0' && ((*c == 32) || (9 <= *c && *c <= 13)))
	{
		c++;
	}
	return (c);
}

static double		iter_digits(char **str, int sign, int is_e)
{
	double num;

	num = 0.0;
	*str += (sign != 0);
	while (ft_isdigit((int)**str))
	{
		num = num * 10.0 + (double)((int)**str - 48);
		(*str)++;
	}
	if (sign < 0 && !is_e)
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
	num = iter_digits(&s, sgn, 0);
	if (*s++ == '.')
		while (*s && ft_isdigit(*s))
		{
			num = num * 10.0 + (double)((int)((*s) - 48));
			e -= 1;
			s++;
		}
	if (*s == 'e' || *s == 'E')
	{
		i = (int)(iter_digits(&s, sgn = get_sign(++s), 1));
		e += (i * sgn);
	}
	sgn = (e >= 0) ? 1 : -1;
	return (calc_mantissa(e, num, sgn));
}