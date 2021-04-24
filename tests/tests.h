#ifndef TESTS_H
# define TESTS_H

# include "minirt.h"
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <float.h>

typedef struct	s_lst
{
	t_list *head;
	t_list *tail;
}				t_lst;

// typedef struct	s_args
// {
// 	void *outwin;
// 	t_conf	*conf;
// }				t_args;

int		put_mouse_pos(int x, int y, t_args *args);

void	*init_infobar(void *mlx, int sizex, int sizey, char *title);
void	test_lines (t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_square (t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_circle (t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_triangle(t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_translate(t_conf *conf, void (*put_line)(t_line *, t_conf *));

// Extra test funcs
	// Misc
void	ft_putint(int nb);
void	ft_putnbr(long nb);
void	ft_putnewline(void);
void	ft_putchar(char c);
void	ft_delineate(char *str);
size_t	ft_strsize(char *str);
void	ft_putcharvals(char *str, size_t len);
void	ft_putblock(void *ptr, size_t len, size_t count);
void	ft_putstrarr(char **arr, size_t len);
// int		ft_is_in(char const c, char const *set);
// size_t	ft_iter_chars(char const *s, char *set, size_t flag);
// size_t	ft_count_words(char const *s, char *set);
// size_t  ft_count_digits(int n, size_t i);
// char	**ft_free_arr(char **arr, size_t len);
	// Linked lists
void	ft_putnode(t_list *node);
void	ft_putlist(t_list *head_node);
void	ft_fill_list_front(t_list **phead, size_t len, char **contents);
void	ft_fill_list_back(t_list **phead, size_t len, char **contents);
t_list	*ft_lstfind_node(t_list **head, char *content);


#endif