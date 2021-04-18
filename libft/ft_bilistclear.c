#include "libft.h"

void    ft_bilistclear(t_bilist **bilist, void(*del)(void *))
{
    t_bilist *current;
    t_bilist *next;

    current = *bilist;
    while (current)
    {
        next = current->next;
        ft_bilistdelone(current, del);
        current = next;
    }
    *bilist = NULL;
}