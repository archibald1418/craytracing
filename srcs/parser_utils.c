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
		if (ft_strncmp(s, arr[i++], ft_strlen(s)) == 0)
			return (1);
	return (0);
}

void		set_color(t_color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = g;
}

double	sign(double x)
{
	if (x < 0)
		return (-1.0);
	if (x > 0)
		return (1.0);
	return (0.0);
}
