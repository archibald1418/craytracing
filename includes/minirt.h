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

// Anumation
typedef struct	s_params
{
	t_square	*square;
	t_win		*vars;
	t_res		*res; 
	t_point		*speed;
	t_data		*data;
	
}				t_params;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_data *data, int x, int y);
int             close_win(t_win *vars);
int 			key_hook (int keycode, t_win *vars);


#endif