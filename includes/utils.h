#ifndef UTILS_H
# define UTILS_H

# include "shapes.h"

void	put_text(void *mlx, void *win, char *str, t_point *loc);
double	calc_der(t_line *a);
double	sign(double x);
size_t	ft_count_words(char const *s, char *set);
size_t	ft_iter_chars(char const *s, char *set, size_t flag);
int		ft_is_in(char const c, char const *set);

#endif