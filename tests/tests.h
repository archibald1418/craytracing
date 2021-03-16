#ifndef TESTS_H
# define TESTS_H

# include "../includes/minirt.h"
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_args
{
	void *outwin;
	t_conf	*conf;
}				t_args;

int		put_mouse_pos(int x, int y, t_args *args);

void	*init_infobar(void *mlx);
void	test_lines (t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_square (t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_circle (t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_triangle(t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	test_translate(t_conf *conf, void (*put_line)(t_line *, t_conf *));

#endif