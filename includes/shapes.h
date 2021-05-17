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

typedef struct	s_plane
{
	t_line	*a;
	t_line	*b;
	int color;
}				t_plane; 

typedef struct	s_sphere
{
	t_p3d	c;
	double	d;
	int 	color;
}				t_sphere; 

typedef struct	s_grad
{
	int dx;
	int dy;
}				t_grad;

// Parsing
typedef struct	s_pl
{
	t_p3d dir;
	t_p3d p;
	t_color	color;
}				t_pl;

typedef struct	s_sq
{
	t_p3d	c;
	t_p3d	dir;
	double	size;
	t_color	color;
}				t_sq;

typedef struct	s_cy
{
	t_p3d	c; // center of mass
	t_p3d	dir;
	double	d;
	double	h;
	t_color	color;
}				t_cy;

typedef struct	s_tr
{
	t_p3d	A;
	t_p3d	B;
	t_p3d	C;
	t_color	color;
}				t_tr;

typedef struct	s_sp
{
	t_p3d	c;
	double	d;
	t_color	color;
}				t_sp;

#endif