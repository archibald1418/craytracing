#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# include "mlx.h"

# include "libft.h"
# include "get_next_line.h"

# include "conf.h"
# include "colors.h"
# include "shapes.h"
# include "vectors.h"
# include "utils.h"
# include "parser.h"

// KEYMAPS:
# define UP		126
# define LEFT	123
# define DOWN	125
# define RIGHT	124
# define ESC	53
# define WKEY      13
# define AKEY      0
# define SKEY      1
# define DKEY      2
# define NUM2      84
# define NUM4      86
# define NUM8      91
# define NUM6      88
# define NUMPLUS   69
# define NUMMINUS  78
# define T         17
# define G         5
# define F         3
# define H         4
# define PLUS      24
# define MINUS     27

// MOUSEMAPS:
# define LCLICK		1
# define RCLICK		2
# define ROLLUP		4
# define ROLLDOWN	5

// EVENTS
# define DestroyNotify			17
# define StructureNotifyMask	1L<<17
# define MotionNotify			6
# define PointerMotionMask 		1L<<6

#define INF	INFINITY

typedef struct   s_conf
{
	t_data  img;
	t_win   vars;
	t_res   res;
	t_bilist *node;
}               t_conf;

typedef struct	s_args
{
	void    *outwin;
	t_conf	*conf;
}				t_args;

typedef struct  s_norm
{
	t_conf  conf;
	t_rt    rt;
	t_args  args;
}
				t_norm;

typedef struct  s_light
{
	t_v3d orient;
	t_ray s_ray;
	t_cam cam;
	t_lsrc lsrc;
	double lightdist;
	int shape_color;
	int total_color;
}               t_light;

// MLX utils
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_data *data, int x, int y);
int             close_win(t_win *vars);
int             key_hook (int keycode, t_norm *norm);
void			put_text(void *mlx, void *win, char *str, t_point *loc);
int				put_mouse_pos(int x, int y, t_args *args);
void			*init_infobar(void *mlx, int sizex, int sizey, char *title);
void			clean_rt(t_rt *rt);
int				do_render(t_conf *conf, t_rt *rt, t_cam *cam);
int				cam_hooks(int keycode, t_cam *cam);
int				do_window(t_norm *norm, t_cam *cam);
void			do_parser(char *path, t_rt *rt);
void			do_bmp(int argc, char **argv, t_norm *norm);

// Colors
int	create_trgb(int t, int r, int g, int b);
int	add_trgb(int trgba, int trgbb, double n);
int	set_lum(int trgb, double lum);
int	get_hex(t_color color);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);
int	get_rgb(int trgb);
int	add_shade(int trgb, double shade);
int	get_opposite(int trgb);

// Intersects
t_color get_shape_color(t_shape shape);
double  intersect_shape(t_shape shape, t_ray ray);
double	plane_intersect(t_pl *pl, t_ray r);
double	square_intersect(t_sq *sq, t_ray r);
double	sphere_intersect(t_sp *sp, t_ray r);
double	triangle_intersect(t_tr *tr, t_ray r);
t_p2d	infinite_cylinder_intersect(t_cy *cy, t_ray r);
double	finite_cylinder_intersect(t_cy *cy, t_ray r, t_p2d roots);
double	sphere_intersect(t_sp *sp, t_ray r);

// Render funcs
ssize_t render(t_conf *conf, t_rt *rt, t_cam cam);

// Tracers
int trace_shapes(t_ray ray, t_shapes shapes, t_v3d *orient);

// Normals
void	get_sp_normal(t_v3d *orient, t_sp *sp, t_ray ray);
void	get_pl_normal(t_v3d *orient, t_pl *pl, t_ray ray);
void	get_sq_normal(t_v3d *orient, t_sq *sq, t_ray ray);
void	get_tr_normal(t_v3d *orient, t_tr *tr, t_ray ray);
void	get_cy_normal(t_v3d *orient, t_cy *cy, t_ray ray);
void    calc_point_normal(t_v3d *orient, t_shape shape, t_ray ray);

// Calc_light
double	diffuse(t_v3d orient, t_ray l_ray);
double	specular(t_v3d orient, t_ray l_ray, t_cam cam);
double	phong(t_v3d orient, t_ray l_ray, t_cam cam, double base_lum);
int		apply_shade(t_light light);
int		calc_lights(int color, t_v3d orient, t_rt *rt, t_cam cam);
int		accumulate_color(int prev, int curr);
t_light set_light(t_rt *rt, t_v3d orient, t_cam cam, int shape_color);

// Matrix opeartions
t_matrix	init_matrix(t_p3d X, t_p3d Y, t_p3d Z);
t_matrix	get_unit_matrix(void);
t_p3d  		mat_mult_vec(t_matrix m, t_p3d vec);
t_matrix	get_new_basis(t_p3d tmp, t_cam cam);
t_matrix	get_rotation(t_cam cam);
t_matrix	get_rot_x(t_cam cam);
t_matrix	get_rot_y(t_cam cam);
t_matrix	get_rot_z(t_cam cam);
t_p3d		rot_ray(t_cam cam, t_ray ray);

// .bmp screenshot
int save_bmp(t_conf *conf);
// void	set_fileheader(t_res res, int fd);
void	set_fileheader(t_res res, int fd);

// Errors
int	has_extension(char *filename, char *ext);
int handle_errors(char *msg);

#endif