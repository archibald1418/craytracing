#ifndef UTILS_H
# define UTILS_H

double	sign(double x);
size_t	ft_count_words(char const *s, char *set);
size_t	ft_iter_chars(char const *s, char *set, size_t flag);
int		ft_is_in(char const c, char const *set);

// Equations
double	get_min_pos_root(double disc, double a, double b);

#endif