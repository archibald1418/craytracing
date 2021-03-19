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