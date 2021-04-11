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

void		init_v3d(t_v3d *v, double x, double y, double z);
void		init_p3d(t_p3d *p, double x, double y, double z);
int			is_equal(t_point *a, t_point *b);
void		move_point(t_point *a, t_point *offset);
double		get_len(t_p3d *v);
void		p_add(t_p3d *c,t_p3d *v, t_p3d *u);
void		p_sub(t_p3d *c, t_p3d *v, t_p3d *u);
void		scaldiv(t_p3d *c, t_p3d *v, double s);
void		scalmult(t_p3d *c, t_p3d *v, double s);
void		normalize(t_p3d *n, t_p3d *v);
double		dot(t_p3d *v, t_p3d *u);
double		dotAlpha(t_v3d *v, double angle);
double		cosSim(t_v3d *v, t_v3d *u);
void		p_mult(t_p3d *c, t_p3d *v, t_p3d *u);
double		det2(t_p2d *v, t_p2d *u);
void		cross(t_p3d *c, t_p3d *v, t_p3d *u);
void		init_ray(t_v3d *ray, t_res *res, int px, int py, double fov);

#endif