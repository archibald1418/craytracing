#ifndef UTILS_H
# define UTILS_H

double	sign(double x);
size_t	ft_count_words(char const *s, char *set);
size_t	ft_iter_chars(char const *s, char *set, size_t flag);
int		ft_is_in(char const c, char const *set);
int     get_sign(char *str);
double	get_esgn(double esgn);
int	t_min_max(int n, int min, int max);

// Equations
double	get_min_pos_root(double disc, double a, double b);

#endif