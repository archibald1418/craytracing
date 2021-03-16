#ifndef UTILS_H
# define UTILS_H

# include "shapes.h"

void	put_text(void *mlx, void *win, char *str, t_point *loc);
double	calc_der(t_line *a);
double	get_sign(double x);

#endif