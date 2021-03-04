#include "minirt.h"
#include "tests.h"
#include <time.h>

void test_lines (t_win *vars, t_data *data, t_res *res, void (*put_line)(t_line *, t_win *, t_data *))
{
	// Diagonal +
	t_point p1 =  (t_point){0, 0};
	t_point p2 = {res->X, res->Y};
	t_line l1 = {&p1, &p2, cyan};

	// Diagonal -
	t_point p3 =  (t_point){res->X, 0};
	t_point p4 = {0, res->Y};
	t_line l2 = {&p3, &p4, magenta};

	// Vertical up
	t_point p5 = {1, 1};
	t_point p6 = (t_point){res->X - res->X*1/3, res->Y};
	t_line l3 = {&p5, &p6, red};

	// Vertical down
	t_point p7 =  (t_point){res->X, 1};
	t_point p8 = {res->X - res->X*1/3, res->Y};
	t_line l4 = {&p7, &p8, green};

	// Horizontal left
	t_point p9 =  (t_point){res->X, 1*res->Y/3};
	t_point p10 = {1, 1*res->Y/3};
	t_line l5 = {&p9, &p10, blue};

	// Horizontal right
	t_point p11 =  (t_point){1, 2*res->Y/3};
	t_point p12 = {res->X, 2*res->Y/3};
	t_line l6 = {&p11, &p12, yellow};

	// One pixel
	t_point p13 = {res->X/2, res->Y/2};
	t_point p14 = p13;
	t_line l7 = {&p13, &p14, black};

	init_window(vars, res, "Line tests!");
	init_img(data, vars, res->X, res->Y);
	
	int i = 0;
	t_line lines[8] = {l1, l2, l3, l4, l5, l6, l7};
	char *titles[8] = {"Diagonal +\n\n", "Diagonal -\n\n", "Vertical up\n\n", "Vertical down\n\n", "Horizontal left\n\n", "Horizontal right\n\n", "One pixel\n\n"};
	while (i < 7)
	{
		dprintf(1, "%s", titles[i]);
		put_line(&(lines[i]), vars, data);
		i++;
	}

}

void test_square (t_win *vars, t_data *img, t_res *res, void (*put_line)(t_line *, t_win *, t_data *))
{
	;
}

void test_circle (t_win *vars, t_data *img, t_res *res)
{
	;
}

void test_triangle (t_win *vars, t_data *img, t_res *res)
{
	;
}

void test_translate(t_conf *conf)
{

	// // Horizontal left
	// t_point p9 =  (t_point){conf->res->X, 1};
	// t_point p10 = {1, 1};
	// t_line l5 = {&p9, &p10, magenta};
	// // t_grad g1 = (t_grad){1, 1};

	t_grad rate = {1, 1};

	// Slant +
	t_grad tmp[sizeof(t_grad)];
	
	t_point p1 = {200, 200};
	t_point p2 = {400, 300};
	t_line l1 = {&p1, &p2, white};

	// t_point p3 = {400, 200};
	// t_point p4 = {600, 650};
	// t_line	l2[sizeof(t_line)];
	// copy_line(l2, &l1);
	// move_line(line, (t_point));
	// t_point offset

	put_line_naive(&l1, conf);
	ft_memcpy(tmp, &rate, sizeof(t_grad));

	int side = 300;
	int i = 0;
	while (i < side - 1)
	{
		translate_line(&l1, (t_grad *)&tmp, conf); // TODO: move coords func + translate_line
		i++;
		// tmp->dx += rate.dx;
		// tmp->dy += rate.dy;
	}
}

void	render_next_frame()
{
	;
}

int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;

	t_conf	conf;

	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");

	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, "Line translate!");
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// put_square(&(t_square){&(t_point){0, 0}, res.X, white}, &conf);
	// Test lines!
	// test_lines(&vars, &img, &res, put_line_naive);
	test_translate(&conf);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_loop(vars.mlx);
}