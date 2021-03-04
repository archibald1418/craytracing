#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct s_dir
{
	double x;
	double y;
}			t_dir;

typedef struct	s_vector
{
	t_point *point;
	t_dir	*dir;
}				t_vector;

int		is_equal(t_point *a, t_point *b);
void	move_point(t_point *a, t_point *offset);

#endif