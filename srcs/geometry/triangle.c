#include "minirt.h"

void	init_triangle(t_triangle *tr, t_point *A, t_point *B, t_point *C, int color)
{
	tr->A = A;
	tr->B = B;
	tr->C = C;
	tr->color = color;
}

void	put_triangle(t_triangle *tr, t_conf *conf, void (*put_line)(t_line *, t_conf *))
{
	t_line a;
	t_line b;
	t_line c;

	init_line(&a, tr->A, tr->B, tr->color);
	init_line(&b, tr->B, tr->C, tr->color);
	init_line(&c, tr->A, tr->C, tr->color);

	put_line(&a, conf);
	put_line(&b, conf);
	put_line(&c, conf);
}

t_triangle	*copy_triangle(t_triangle *dst, t_triangle *src)
{
	return ((t_triangle *)ft_memcpy(dst, src, sizeof(t_triangle)));
}

void	move_triangle(t_triangle *tr, t_point *offset)
{
	move_point(tr->A, offset);
	move_point(tr->B, offset);
	move_point(tr->C, offset);
}

void	translate_triangle(t_triangle *tr, t_grad *g, t_conf *conf, void (*put_line)(t_line *, t_conf *))
{
	t_triangle tmp[sizeof(t_triangle)];

	copy_triangle(tmp, tr);
	move_triangle(tmp, (t_point *)g);
	put_triangle((t_triangle *)tmp, conf, put_line);
}


// int main()
// {
// 	t_win	vars;
// 	t_res	res;
// 	t_data	img;
// 	t_args args;

// 	t_conf	conf;

// 	res.X = ft_atoi("1000");
// 	res.Y = ft_atoi("1000");

// 	conf = (t_conf){&img, &vars, &res};
// 	init_window(conf.vars, conf.res, "Line dda!");
// 	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
// 	// put_square(&(t_square){&(t_point){0, 0}, res.X, white}, &conf);
// 	// Test lines!

// 	// Infobar
// 	args.outwin = init_infobar(conf.vars->mlx);
// 	args.conf = &conf;

// 	test_lines(&conf, put_line_dda);
// 	test_translate(&conf, put_line_dda);

// 	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
// 	mlx_key_hook(vars.win, key_hook, &vars);
// 	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
// 	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
// 	mlx_loop(vars.mlx);
// }