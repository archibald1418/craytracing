/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:20:11 by ldonita           #+#    #+#             */
/*   Updated: 2021/04/21 00:02:40 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, size_t size)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list *));
	if (newnode != NULL)
	{
		newnode->content = ft_memdup(content, size);
		newnode->next = NULL;
	}
	return (newnode);
}
