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

typedef struct	s_args
{
	void *outwin;
	t_conf	*conf;
}				t_args;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_data *data, int x, int y);
int             close_win(t_win *vars);
int 			key_hook (int keycode, t_win *vars);
void			put_text(void *mlx, void *win, char *str, t_point *loc);
int				put_mouse_pos(int x, int y, t_args *args);
void			*init_infobar(void *mlx, int sizex, int sizey, char *title);


// Intersects
t_color get_shape_color(t_shape shape);
double  intersect_shape(t_shape shape, t_ray ray);
double	plane_intersect(t_pl *pl, t_ray r);
double	sphere_intersect(t_sp *sp, t_ray r);

// Render funcs
ssize_t render(t_conf *conf, t_rt *rt, t_cam cam);

// Tracers
int trace_shapes(t_ray ray, t_shapes shapes, t_v3d *orient);

// Normals
void    get_sp_normal(t_v3d *orient, t_sp *sp, t_ray ray);
void    calc_point_normal(t_v3d *orient, t_shape shape, t_ray ray);

// Calc_light
int	calc_lights(int color, t_v3d orient, t_rt *rt);

// Matrix opeartions
double	**init_matrix(t_p3d X, t_p3d Y, t_p3d Z);
double  **get_unit_matrix(void);
t_p3d   mat_mult_vec(double m[3][3], t_p3d vec);
double  **get_new_basis(t_p3d tmp, t_cam cam);
double  **get_rotation(t_cam cam);

#endif