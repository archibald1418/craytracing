#ifndef SHAPES_H
# define SHAPES_H

# include "vectors.h"

typedef struct	s_square
{
	t_point	*start;
	int		side;
	int		color;
}				t_square;

typedef struct	s_circle
{
	t_point	*center;
	int		rad;
	int		color;
}				t_circle;

typedef struct	s_args
{
	void	*shape;
	int		side;
	int		color;
	void	*point;
}				t_args;

// void 	init_shape(void *shape, void (*draw)(void *shape), void	(*init)(t_args *args));
// typedef struct	s_shape
// {
// 	void		*shape;
// 	void		(*put)(void *shape);
// 	void		(*init)(void *shape);
// }				t_shape;
void	init_square(t_square *square, int side, int color, t_point *start);
void	put_square (t_square *square, t_win *vars, t_data *data);
void	init_circle(t_circle *circle, int rad, int color, t_point *center);
void	put_circle(t_circle *circle, t_win *vars, t_data *data);

#endif