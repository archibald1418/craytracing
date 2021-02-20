#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "colors.h"

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_res
{
	int X;
	int Y;
}				t_res;

#endif