#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_p3d
{
	double x;
	double y;
	double z;
}				t_p3d;

typedef struct	s_p2d
{
	double x;
	double y;
}				t_p2d;

typedef struct s_dir
{
	double x;
	double y;
}			t_dir;

typedef struct	s_vector
{
	t_p2d	loc;
	t_p2d	dir;
}				t_vector;

typedef struct	s_v3d
{
	t_p3d	loc;
	t_p3d	dir;
}				t_v3d;

typedef struct	s_matrix
{
	double m[3][3];
}				t_matrix;

typedef t_v3d t_ray;

// Vector operations
t_v3d		init_v3d(t_v3d *v, t_p3d loc, t_p3d dir);
t_p3d		init_p3d(t_p3d *p, double x, double y, double z);
int			is_equal(t_point *a, t_point *b);
void		move_point(t_point *a, t_point *offset);
double		get_len(t_p3d v);
t_p3d		p_add(t_p3d *c,t_p3d v, t_p3d u);
t_p3d		p_sub(t_p3d *c, t_p3d v, t_p3d u);
t_p3d		p_mult(t_p3d *c, t_p3d v, t_p3d u);
t_p3d		scaldiv(t_p3d *c, t_p3d v, double s);
t_p3d		scalmult(t_p3d *c, t_p3d v, double s);
t_p3d		normalize(t_p3d *n, t_p3d v);
double		dot(t_p3d v, t_p3d u);
double		dot_alpha(t_v3d v, double angle);
double		cos_sim(t_p3d v, t_p3d u);
double		det2(t_p2d v, t_p2d u);
t_p3d		cross(t_p3d *c, t_p3d v, t_p3d u);
int			is_not_zero(t_p3d vec);
t_p3d		get_new_point(t_p3d loc, t_p3d dir, double t);
double		get_dist(t_p3d v, t_p3d u);


#endif