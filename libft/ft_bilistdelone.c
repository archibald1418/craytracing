/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilistdelone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:53:39 by ldonita           #+#    #+#             */
/*   Updated: 2021/04/20 23:53:50 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_bilistdelone(t_bilist *bilist, void(*del)(void *))
{
    del(bilist->content);
    free(bilist);
}