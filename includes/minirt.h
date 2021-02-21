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

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

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

typedef struct	s_square
{
	t_point	*start;
	int		side;
	int		color;
}				t_square;

typedef struct	s_params
{
	t_square	*square;
	t_vars		*vars;
	t_res		*res; 
	t_point		*speed;
	t_data		*data;
}				t_params;



int             close_win(t_vars *vars);


#endif