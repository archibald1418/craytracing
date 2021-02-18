/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 04:59:24 by ldonita           #+#    #+#             */
/*   Updated: 2021/02/18 16:29:45 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_chnk	*ft_lstnew_(size_t len)
{
	t_chnk *new;
	size_t i;

	if (!(new = (t_chnk *)malloc(sizeof(t_chnk))))
		return (NULL);
	if (!(new->text = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	new->len = len;
	i = 0;
	while (i <= len)
	{
		(new->text)[i] = '\0';
		i++;
	}
	new->next = NULL;
	return (new);
}

void	ft_lstappend_back_null(t_last *last, t_chnk *node)
{
	if (node == NULL)
		return ;
	if (last->head == NULL)
	{
		last->head = node;
		last->tail = node;
		return ;
	}
	last->tail->next = node;
	node->next = NULL;
	last->tail = node;
}

ssize_t	ft_lstclear_(t_chnk **lst)
{
	t_chnk *current;
	t_chnk *next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->text);
		current->text = NULL;
		free(current);
		current = NULL;
		current = next;
	}
	*lst = NULL;
	return (-1);
}

char	*ft_lstjoin(t_chnk **phead, char **line)
{
	t_chnk	*node;
	char	*pline;
	size_t	sumlen;

	node = *phead;
	sumlen = 0;
	while (node)
	{
		sumlen += node->len;
		node = node->next;
	}
	if (!(*line = malloc(sizeof(char) * (sumlen + 1))))
		return (NULL);
	node = *phead;
	pline = *line;
	while (node)
	{
		ft_memmove(pline, node->text, node->len);
		pline += node->len;
		node = node->next;
	}
	*pline = '\0';
	return (*line);
}
