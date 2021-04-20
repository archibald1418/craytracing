/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilistappend_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:53:31 by ldonita           #+#    #+#             */
/*   Updated: 2021/04/20 23:53:31 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_bilist_append_back(t_bilast *bilast, t_bilist *node)
{
	t_bilist *old_tail;
    if (node == NULL)
		return ;
	if (bilast->head == NULL)
	{
		bilast->head = node;
		bilast->tail = node;
		return ;
	}
	old_tail = bilast->tail;
	node->prev = old_tail;
	old_tail->next = node;
	bilast->tail = node;
}
