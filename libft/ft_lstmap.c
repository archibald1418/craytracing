/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:51:48 by ldonita           #+#    #+#             */
/*   Updated: 2021/04/20 23:51:49 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*tmp;
	t_list	*new_head;

	tmp = lst;
	new_head = ft_lstnew(f(lst->content), ft_strlen((char *)f(lst->content)));
	while (tmp->next)
	{
		newnode = (t_list *)ft_lstnew(f(tmp->next->content), \
							ft_strlen((char *)f(tmp->next->content)));
		ft_lstadd_back(&new_head, newnode);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, del);
	return (new_head);
}
