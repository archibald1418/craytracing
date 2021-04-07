#include "minirt.h"
#include "tests.h"

typedef struct	s_info
{
	t_vector *v;
	t_args	*args;
}				t_info;

double	get_veclen(t_vector *v, t_p2d *end)
{
	// Длина относительно начального положения вектора (а не нуля)
	
	return ((double)hypot(end->x - v->loc->x, end->y - v->loc->y));
}


void	init_v2d(t_vector *v, t_p2d *loc, t_p2d *dir)
{
	v->loc = loc;
	v->dir = dir;
}

void	put_vecinfo(t_vector *v, t_p2d *end, char *label, t_point *pos, t_args *args)
{
	char fmt_label[100];
	char fmt_loc[100];
	char fmt_dir[100];
	char fmt_len[100];	

	mlx_clear_window(args->conf->vars->mlx, args->outwin);
	sprintf(fmt_label, "%s", label);
	sprintf(fmt_loc, ".loc=(%6.2f,%6.2f)", v->loc->x, v->loc->y);
	sprintf(fmt_dir, ".dir=(%6.2f,%6.2f)", v->dir->x, v->dir->y);
	sprintf(fmt_len, ".len=%6.2f", get_veclen(v, end));

	// Put label
	t_point pos1 = {10, 50};
	t_point pos2 = {10, 100};
	t_point pos3 = {10, 150};
	t_point pos4 = {10, 200};

	put_text(args->conf->vars->mlx, args->outwin, fmt_label, &pos1);
	put_text(args->conf->vars->mlx, args->outwin, fmt_loc, &pos2);
	put_text(args->conf->vars->mlx, args->outwin, fmt_dir, &pos3);
	put_text(args->conf->vars->mlx, args->outwin, fmt_len, &pos4);
	
}	

int		put_vec_pos(int x, int y, t_info *info)
{
	// x and y are mouse coordinates 

	t_vector *v = info->v;
	t_p2d end;
	double len;

	t_args *args = info->args;
	
	int		i = 0;
	// while (i < )
	// {
	// 	/* code */
	// }
	
	ft_bzero(args->conf->img->addr, \
	sizeof(char) * args->conf->img->line_length * info->args->conf->res->X);
	if (0 <= x && x <= args->conf->res->X && \
		0 <= y && y <= args->conf->res->Y)
	{
		// Tag vector lmao!
		end.x = (double)x;
		end.y = (double)y;

		// Calc new len
		len = get_veclen(v, &end);

		// Calc new normal (should be in [-1, 1])
		v->dir->x = (end.x - v->loc->x) / len;
		v->dir->y = (end.y - v->loc->y) / len;

		if ((0 <= end.x && end.x < args->conf->res->X) || \
			(0 <= end.y && end.y < args->conf->res->Y))
		{
			draw_vector(v->loc, &end, args->conf, put_line_dda);
			put_vecinfo(v, &end, "A", &(t_point){10, 30}, args); 
			mlx_put_image_to_window(args->conf->vars->mlx, args->conf->vars->win, args->conf->img->img, 0, 0);
		}
	}
	return (0);
}

int	cls(t_win *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	return (0);
}

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;
	t_args args;
	t_args	args2;

	t_conf	conf;

	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");	

	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, "AAAAA VECTORS!");
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// put_square(&(t_square){&(t_point){0, 0}, res.X, white}, &conf);
	// Test lines!

	// Infobar rgb
	args.outwin = init_infobar(conf.vars->mlx, 210, 210, "RGB!");
	args.conf = &conf;

	// Infobar vector
	args2.outwin = init_infobar(conf.vars->mlx, 500, 500, "Coords!");
	args2.conf = &conf;

	// Init fixed vector
	t_vector v;
	v.loc = &(t_p2d){res.X / 2, res.Y/2};
	v.dir = &(t_p2d){1, 1};

	// Init info
	t_info info;
	info.v = &v;
	info.args = &args2;
	// test_translate(&conf, put_line_naive);
	// test_lines(&conf, put_line_dda);

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_vec_pos, &info);
	// mlx_loop_hook(vars.mlx, cls, &vars);
	mlx_loop(vars.mlx);
}