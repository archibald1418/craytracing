#ifndef VECTORS_H
# define VECTORS_H
# include "shapes.h"


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
	t_p2d	*loc;
	t_p2d	*dir;
}				t_vector;

typedef struct	s_v3d
{
	t_p3d	*loc;
	t_p3d	*dir;
}				t_v3d;

typedef t_v3d		t_norm3d;
// typedef t_v2d		t_norm2d;
typedef t_v3d		t_ray;

void		init_v3d(t_v3d *v, double x, double y, double z);
int			is_equal(t_point *a, t_point *b);
void		move_point(t_point *a, t_point *offset);
double		get_len(t_p3d *v);
void		p_add(t_p3d *c,t_p3d *v, t_p3d *u);
void		p_sub(t_p3d *c, t_p3d *v, t_p3d *u);
void		scaldiv(t_p3d *c, t_p3d *v, double s);
void		normalize(t_p3d *n, t_p3d *v);
double		dot(t_p3d *v, t_p3d *u);
double		dotAlpha(t_v3d *v, double angle);
double		cosSim(t_v3d *v, t_v3d *u);
void		p_mult(t_p3d *c, t_p3d *v, t_p3d *u);
double		det2(t_point *v, t_point *u);
void		cross(t_p3d *c, t_p3d *v, t_p3d *u);
void		draw_vector(t_p2d *v, t_p2d *end, t_conf *conf, void (*put_line)(t_line *, t_conf *));
void		init_ray(t_ray *ray, int W, int H, int px, int py, double fov);

#endif