#include "libft.h"

t_bilist  *ft_bilistnew(void *content, size_t size)
{
    t_bilist    *node;

    if (!(node = (t_bilist *)malloc(sizeof(t_bilist))))
        return (NULL);
    if (!(node->content = ft_memdup(content, size)))
        return (NULL);
    node->next = NULL;
    node->prev = NULL;
    return(node);
}