/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonita <ldonita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 05:01:16 by ldonita           #+#    #+#             */
/*   Updated: 2021/02/18 18:17:44 by ldonita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	10
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_chnk
{
	char			*text;
	size_t			len;
	struct s_chnk	*next;
}					t_chnk;

typedef struct		s_last
{
	t_chnk			*head;
	t_chnk			*tail;
}					t_last;

ssize_t				ft_memchri(const void *s, int c, size_t n);
void				*ft_memdup(const void *s, size_t size);
void				*ft_memmove(void *dst, const void *src, size_t len);
t_chnk				*ft_lstnew_(size_t len);
void				ft_lstappend_back_null(t_last *last, t_chnk *node);
ssize_t				ft_lstclear_(t_chnk **lst);
char				*ft_lstjoin(t_chnk **phead, char **line);
int					parse_buffer(t_last *last, t_chnk *chunk, char **line);
int					get_next_line(int fd, char **line);

#endif
