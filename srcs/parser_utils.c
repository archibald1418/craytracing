#include "minirt.h"

void			**free_arr(void **arr, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
	return ((void **)NULL);
}

int			is_in_arr(char *s, char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strcmp(s, arr[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}


double	sign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
}

size_t		ft_count_words(char const *s, char *set)
{
	size_t flag;
	size_t words;

	flag = 1;
	words = 0;
	while (*s != '\0')
	{
		s += ft_iter_chars(s, set, flag);
		if (flag == 0)
			words++;
		flag = !flag;
	}
	return (words);
}

size_t		ft_iter_chars(char const *s, char *set, size_t flag)
{
	size_t i;

	i = 0;
	while ((((size_t)ft_is_in(s[i], set) == flag)) && (s[i] != '\0'))
		i++;
	return (i);
}

int		ft_is_in(char const c, char const *set)
{
	size_t i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}