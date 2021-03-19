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

typedef struct	s_bilist
{
	t_list *list;
	t_list *prev;
}				t_bilist;

typedef struct	s_shapes
{
	void		*shapes[MAX_SHAPES];
	int			top; //	 Заполненность массива
}				t_shapes;

typedef t_list		t_lsrcs;
typedef t_bilist	t_cams;

typedef struct	s_rt
{
	t_res		*res;
	t_lamb		*lamb;
	t_shapes	*shapes;
	t_lsrcs		*lsrcs;
	t_cams		*cams;
}				t_rt;

double	ft_atof(char *s);
char	**ft_strsplit(char const *s, char *set);
void	**free_arr(void **arr, size_t len);
void	parser(char *path);
void	init_rt(t_rt *rt);
int		check_rt(t_rt *rt);
int		is_in_arr(char *s, char **arr);

#endif