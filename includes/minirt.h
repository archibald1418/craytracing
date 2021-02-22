#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# include "mlx.h"

# include "libft.h"
# include "get_next_line.h"

# include "conf.h"
# include "colors.h"
# include "shapes.h"
# include "vectors.h"

// KEYMAPS:
# define UP		126
# define LEFT	123
# define DOWN	125
# define RIGHT	124
# define ESC	53

// EVENTS
# define DestroyNotify			17
# define StructureNotifyMask	1L<<17


typedef struct	s_shape
{
	void		*shape;
	void		(*calc)(void *shape);
}				t_shape;

typedef struct	s_params
{
	t_square	*square;
	t_vars		*vars;
	t_res		*res; 
	t_point		*speed;
	t_data		*data;
	
}				t_params;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
int             close_win(t_vars *vars);
int 			key_hook (int keycode, t_vars *vars);


#endif