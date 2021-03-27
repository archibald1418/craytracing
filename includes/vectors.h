#ifndef VECTORS_H
# define VECTORS_H
# include "shapes.h"


typedef struct	s_p3d
{
	double x;
	double y;
	double z;
}				t_p3d;

typedef struct s_dir
{
	double x;
	double y;
}			t_dir;

typedef struct	s_vector
{
	t_point *loc;
	t_dir	*dir;
}				t_vector;

typedef struct	s_v3d
{
	t_p3d	*loc;
	t_p3d	*dir;
}				t_v3d;

typedef t_v3d		t_norm3d;
// typedef t_v2d		t_norm2d;
typedef t_vector	t_ray;

void		init_v3d(t_v3d *v, double x, double y, double z);
int			is_equal(t_point *a, t_point *b);
void		move_point(t_point *a, t_point *offset);
void		vecAdd(t_v3d *c,t_v3d *v, t_v3d *u);
void		vecSub(t_v3d *c, t_v3d *v, t_v3d *u);
double		get_len(t_v3d *v);
void		scaldiv(t_v3d *c, t_v3d *v, double s);
void		scalmult(t_v3d *c, t_v3d *v, double s);
void		normalize(t_norm3d *n, t_v3d *v);
double		dot(t_v3d *v, t_v3d *u);
double		dotAlpha(t_v3d *v, double angle);
double		cosSim(t_v3d *v, t_v3d *u);
void		vecMult(t_v3d *c, t_v3d *v, t_v3d *u);
double		det2(t_point *v, t_point *u);
void		cross(t_v3d *c, t_v3d *v, t_v3d *u);
void		draw_vector(t_vector *vec, t_conf *conf, void* put_line(t_line*, t_conf*), int scalar);

#endif