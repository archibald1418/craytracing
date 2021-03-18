#include "libft.h"

static int		is_int(long num)
{
	return (INT_MIN <= num && num <= INT_MAX);
}

static char		*iter_spaces(char *c)
{
	while (*c != '\0' && ((*c == 32) || (9 <= *c && *c <= 13)))
	{
		c++;
	}
	return (c);
}

static long		iter_digits(const char *str, int sign)
{
	long num;

	num = 0;
	str += (sign != 0);
	while (ft_isdigit((int)*str) && is_int(num))
	{
		num = num * 10 + ((int)*str - 48);
		str++;
	}
	if (sign < 0)
		return (num * -1);
	return (num);
}

static int		get_sign(const char *str)
{
	if (*(unsigned char *)str == '+')
		return (1);
	if (*(unsigned char *)str == '-')
		return (-1);
	return (0);
}


double	ft_atof(char *s)
{
	return (0.0);
}