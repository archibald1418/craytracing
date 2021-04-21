#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "get_next_line.h"

# include "conf.h"
# include "light.h"
# include "shapes.h"
# include "colors.h"
# include "camera.h"
# include "utils.h"



// # define MAX_CAM 100
# define MAX_SHAPES	100

// typedef struct	s_bilist
// {
// 	t_list	*next;
// 	t_list	*prev;
// 	void	*content;
// }				t_bilist;

typedef struct	s_shapes
{
	void		*shapes[MAX_SHAPES];
	int			top; //	 Заполненность массива
}				t_shapes;

typedef t_list		t_lsrcs;
typedef t_bilist	t_cams;

typedef struct	s_rt
{
	t_res		res;
	t_lamb		lamb;
	t_shapes	*shapes;
	t_list		*lsrcs;
	t_bilast	cams;
}				t_rt;

double	ft_atof(char *s);
char	**ft_strsplit(char const *s, char *set);
void	**free_arr(void **arr, size_t len);
int		parser(const char *path, t_rt *rt);
void	init_rt(t_rt *rt);
void	set_color(t_color *col, int r, int g, int b);
void	set_lamb(t_lamb *lamb, double lum, t_color *col);

// Scene checkers
int		check_rt(t_rt *rt);
int		check_res (char **tokens, t_rt *rt);
int		check_rgb(char ***tokens, t_color *color);
int		check_lamb(char **tokens, t_rt *rt);
int		check_rt(t_rt *rt);

int		check_cam (char **tokens, t_cam *cam);
int		check_point(char ***tokens, t_p3d *p, int is_normal);
int		check_fov(int fov);

int		is_in_arr(char *s, char **arr);

// Bilist methods



#endif