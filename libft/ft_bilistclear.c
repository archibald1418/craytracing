/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilistclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:53:35 by ldonita           #+#    #+#             */
/*   Updated: 2021/04/20 23:53:51 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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