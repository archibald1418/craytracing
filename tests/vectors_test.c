#include "minirt.h"
#include "tests.h"

typedef struct	s_info
{
	t_vector *v;
	t_args	*args;
}				t_info;

double	get_veclen(t_point *end)
{
	return (sqrt(pow(end->x, 2) + pow(end->y, 2)));
}

void	init_v2d(t_vector *v, t_point *loc, t_point *dir)
{
	v->loc = loc;
	v->dir = dir;
}

char	*get_vecinfo(t_vector *v, t_vector *end, char *label, int scalar)
{
	char *fmt;

	sprintf(fmt,
	"%s:\n.loc=(%6.2f,%6.2f)\n.dir=(%6.2f,%6.2f)\n.len=%6.2f",\
	label,\
	v->loc->x, v->loc->y,\
	v->dir->x, v->dir->y, get_veclen(end));		
	return (fmt);
}	

int		put_vec_pos(int x, int y, t_info *info)
{
	t_vector v[sizeof(*(info->v))];
	t_point end[sizeof(t_point)];
	int scalar;
	double len;

	ft_memcpy(v, info->v, sizeof(*(info->v)));
	ft_memcpy(end, v, sizeof(v));
	scalar = 3;
	len = get_veclen(end);
	t_args *args = info->args;
	if (0 <= x && x <= args->conf->res->X && \
		0 <= y && y <= args->conf->res->Y)
	{
		// Put vector info
		
		v->loc->x = x;
		v->loc->y = y;
		
		t_line line;
		init_line(&line, &(t_point){v->loc->x, v->loc->y}, &(t_point){end->x, end->y}, red);
		// put_line_bresenham()
		put_text(args->conf->vars->mlx, args->outwin, get_vecinfo(v, end,"A", scalar), &(t_point){10, 30}); 
		

		// // Put variable vector info
		// put_text(args->conf->vars->mlx, args->outwin, get_vecinfo(info->v, "A", get_veclen(info->v)), &(t_point){10, 30}); 

		// // Put cross-product vector info
		// put_text(args->conf->vars->mlx, args->outwin, get_vecinfo(info->v, "A", get_veclen(info->v)), &(t_point){10, 30}); 
		
	}
	return (0);
}

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;
	t_args args;

	t_conf	conf;

	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");

	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, "AAAAA VECTORS!");
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// put_square(&(t_square){&(t_point){0, 0}, res.X, white}, &conf);
	// Test lines!

	// Infobar
	args.outwin = init_infobar(conf.vars->mlx);
	args.conf = &conf;

	// test_translate(&conf, put_line_naive);
	test_lines(&conf, put_line_dda);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_loop(vars.mlx);
}