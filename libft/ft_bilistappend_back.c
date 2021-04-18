#include "libft.h"

void    ft_bilist_append_back(t_bilast *bilast, t_bilist *node)
{
    if (node == NULL)
		return ;
	if (bilast->head == NULL)
	{
		bilast->head = node;
		bilast->tail = node;
		return ;
	}
	bilast->tail->next = node;
	node->next = NULL;
	bilast->tail = node;
}
