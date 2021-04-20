/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilistnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:53:44 by ldonita           #+#    #+#             */
/*   Updated: 2021/04/20 23:53:49 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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