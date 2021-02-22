#ifndef SHAPES_H
# define SHAPES_H

# include "vectors.h"

typedef struct	s_square
{
	t_point	*start;
	int		side;
	int		color;
}				t_square;

void	init_square(t_square *square, int side, int color, t_point *start);
void	put_square (t_square *square, t_vars *vars, t_data *data);

#endif