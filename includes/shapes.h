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
	t_point *center;
	int		rad;
	int		color;
}				t_circle;

typedef struct	s_line
{
	t_point		*A;
	t_point		*B;
	int			color;
}				t_line;

typedef struct	s_triangle
{
	t_point *A;
	t_point *B;
	t_point	*C;
	int		color;
}				t_triangle;



// Square & circle
void	init_square(t_square *square, int side, int color, t_point *start);
void	put_square (t_square *square, t_win *vars, t_data *data);
void	init_circle(t_circle *circle, int rad, int color, t_point *center);
void	put_circle(t_circle *circle, t_win *vars, t_data *data);

// Line
void	init_line(t_line *line, t_point *A, t_point *B, int color);
void	put_line_naive(t_line *line, t_win *vars, t_data *data);
void	put_line_dda(t_line *line);
void	put_line_bresenheim(t_line *line);
void	put_line_wu(t_line *line);

#endif