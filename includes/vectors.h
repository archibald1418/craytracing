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

int			is_equal(t_point *a, t_point *b);
void		move_point(t_point *a, t_point *offset);
void		init_v3d(t_v3d *v, double x, double y, double z);
void		move_point(t_point *a, t_point *offset);
t_v3d		*vecAdd(t_v3d *v, t_v3d *u);
t_v3d		*vecSub(t_v3d *v, t_v3d *u);
double		get_len(t_v3d *v);
t_v3d		*scaldiv(t_v3d *v, double s);
t_norm3d	*normalize(t_v3d *v);
double		dot(t_v3d *v, t_v3d *u);
double		dotAlpha(t_v3d *v, double angle);
double		cosSim(t_v3d *v, t_v3d *u);
void		vecMult(t_v3d *v, t_v3d *u);
double		det2(t_point *v, t_point *u);
void		cross(t_v3d *c, t_v3d *v, t_v3d *u);

#endif