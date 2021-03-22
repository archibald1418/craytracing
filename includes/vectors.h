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

typedef struct	s_v3d
{
	double x;
	double y;
	double z;
}				t_v3d;

typedef t_v3d		t_norm3d;
// typedef t_v2d		t_norm2d;
typedef t_vector	t_ray;

int		is_equal(t_point *a, t_point *b);
void	move_point(t_point *a, t_point *offset);

#endif