#include "minirt.h"

static double	ssign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
}

static double	calc_mantissa(int e, double num, int sgn, int esign)
{
	double	mult;

	mult = 0.1;
	if (esign >= 0)
		mult = 10.0;
	while (e != 0)
	{
		num *= mult;
		e -= esign;
	}
	if (sgn == -1)
		return (num * -1);
	return (num);
}

static double	iter_digits(char **str, int sgn)
{
	double	num;

	num = 0.0;
	*str += (sgn != 0);
	while (ft_isdigit((int)**str))
	{
		num = num * 10.0 + (double)((int)**str - '0');
		(*str)++;
	}
	return (num);
}

static int	get_sign(char *str)
{
	if (*(unsigned char *)str == '+')
		return (1);
	if (*(unsigned char *)str == '-')
		return (-1);
	return (0);
}

static void	iter_frac(double *num, int *e, char **s)
{
	while (ft_isdigit(**++s))
	{
		*num = *num * 10.0 + (double)(**s - '0');
		*e -= 1;
	}	
}

double	get_esgn(double esgn)
{
	if (esgn >= 0)
		return (1);
	return (-1);
}

void	kek(double *num, int *e, char **s)
{
	while (ft_isdigit(*++(*s)))
	{
		*num = *num * 10.0 + (double)(**s - '0');
		*e -= 1;
	}
}

double	ft_atof(char *s)
{
	int		e;
	double	num;
	double	esgn;
	int		sgn;
	int		i;

	e = 0;
	i = 0;
	sgn = get_sign(s);
	num = iter_digits(&s, sgn);
	if (*s == '.')
		kek(&num, &e, &s);
	if (*s == 'e' || *s == 'E')
	{
		esgn = get_sign(++s);
		i = (double)(iter_digits(&s, esgn));
		esgn = get_esgn(esgn);
		e += (i * esgn);
	}
	if (*s != '\0')
		return ((double)NAN);
	return (calc_mantissa(e, num, sgn, ssign(e)));
}
