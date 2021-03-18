#include "parser.h"

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
	return ((void **)NULL);
}