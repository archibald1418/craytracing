#include "libft.h"

t_bilist  *ft_bilistnew(void *content, size_t size)
{
    t_bilist    *new;

    if (!(new = malloc(sizeof(t_bilist))))
        return (NULL);
    if (!(new->content = ft_memdup(content, size)))
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
}