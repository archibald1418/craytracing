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
	t_p3d	*c;
	double	d;
	int color;
}				t_sphere;

// TODO: two lines is easy for a color gradient 

typedef struct	s_grad
{
	int dx;
	int dy;
}				t_grad;



// Square & circle
void	init_square(t_square *square, int side, int color, t_point *start);
void	put_square (t_square *square, t_conf *conf);
void	init_circle(t_circle *circle, int rad, int color, t_point *center);
void	put_circle(t_circle *circle, t_conf *conf);

// Lines
void	init_line(t_line *line, t_point *A, t_point *B, int color);
void	put_line_naive(t_line *line, t_conf *conf);
void	put_line_dda(t_line *line, t_conf *conf);
void	put_line_bresenham(t_line *line, t_conf *conf);
void	put_line_wu(t_line *line, t_conf *conf);
void	translate_line(t_line *line, t_grad *g, t_conf *conf, void (*put_line)(t_line *, t_conf *));
t_line *copy_line( t_line *dst, t_line* src);
void	move_line(t_line *line, t_point *offset);
int		are_parallel(t_line *a, t_line *b);
void	draw_vector(t_p2d *v, t_p2d *end, t_conf *conf, void (*put_line)(t_line *, t_conf *));

// Planes
void 	init_plane(t_plane *p, t_line *a, t_line *b, int color);
void	put_plane(t_plane *p, t_conf *conf);

// Triangle
void	init_triangle(t_triangle *tr, t_point *A, t_point *B, t_point *C, int color);
void	put_triangle(t_triangle *tr, t_conf *conf, void (*put_line)(t_line *, t_conf *));
t_triangle	*copy_triangle(t_triangle *dst, t_triangle *src);
void	translate_triangle(t_triangle *tr, t_grad *g, t_conf *conf, void (*put_line)(t_line *, t_conf *));
void	move_triangle(t_triangle *tr, t_point *offset);


#endif