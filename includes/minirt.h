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

#define EPSILON	0.00001
#define INF	INFINITY

typedef struct	s_args
{
	void *outwin;
	t_conf	*conf;
}				t_args;

typedef t_list		t_lsrcs;
typedef t_bilist	t_cams;

typedef struct	s_shape
{
	char	label[4];
	void	*shape;
}				t_shape;

typedef struct	s_shapes
{
	t_shape		shapes[MAX_SHAPES + 1];
	int			top; //	 Заполненность массива
}				t_shapes;

typedef struct	s_rt
{
	t_res		res;
	t_lamb		lamb;
	t_shapes	shapes;
	t_bilast	lsrcs;
	t_bilast	cams;
}				t_rt;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_data *data, int x, int y);
int             close_win(t_win *vars);
int 			key_hook (int keycode, t_win *vars);
void			put_text(void *mlx, void *win, char *str, t_point *loc);
int				put_mouse_pos(int x, int y, t_args *args);
void			*init_infobar(void *mlx, int sizex, int sizey, char *title);

// Render funcs
ssize_t render(t_conf *conf, t_rt *rt);

// Tracers
int trace_shapes(t_ray ray, t_shapes shapes);

#endif