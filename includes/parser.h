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

# define MAX_SHAPES	100

#define SPACES "\v\t \r\f"

# define	RES		(char*)"R"
# define	AMB		(char*)"A"
# define	CAM		(char*)"c"
# define	LS		(char*)"l"
# define	PL		(char*)"pl"
# define	SP		(char *)"sp"
# define	SQ		(char *)"sq"
# define	CY		(char *)"cy"
# define	TR		(char *)"tr"

#define IDLEN	9

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

double	ft_atof(char *s);
char	**ft_strsplit(char const *s, char *set);
void	**free_arr(void **arr, size_t len);
int		parser(const char *path, t_rt *rt);
void	init_rt(t_rt *rt);
void	set_color(t_color *col, int r, int g, int b);
void	set_lamb(t_lamb *lamb, double lum, t_color *col);
void	set_lsrc(t_lsrc *lsrc, double lum, t_color col, t_p3d p);
void	init_rt(t_rt *rt);

// Scene checkers
int		check_rt(t_rt *rt);
int		check_res (char **tokens, t_rt *rt);
int		check_rgb(char ***tokens, t_color *color);
int		check_lamb(char **tokens, t_rt *rt);
int		check_lsrc(char **tokens, t_lsrc *lsrc);
// Shape checkers
int		check_pl(char **tokens, t_rt *rt);
int		check_sp(char **tokens, t_rt *rt);
int		check_tr(char **tokens, t_rt *rt);
int		check_cy(char **tokens, t_rt *rt);
int		check_sq(char **tokens, t_rt *rt);

int		check_cam (char **tokens, t_cam *cam);
int		check_point(char ***tokens, t_p3d *p, int is_normal);
int		check_fov(int fov);

int		is_in_arr(char *s, char **arr);


void	quit_cleanly(t_rt *rt, char ***tokens, char **line);


#endif