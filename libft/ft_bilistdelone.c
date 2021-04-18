#include "libft.h"

void    ft_bilistdelone(t_bilist *bilist, void(*del)(void *))
{
    del(bilist->content);
    free(bilist);
}