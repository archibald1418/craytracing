#include "minirt.h"
#include "tests.h"

/*
Уравнение прямой, проходящей через две точки в R^3

(x - x1) / (x2 - x1) = (y - y1) / (y2 - y1) = (z - z1) / (z2 - z1) 
или
(x - x1)/ax = (y - y1)/ay = (z - z1)/az, где а - направляющий вектор прямой


*/


void	init_sphere(t_sphere *sphere, t_p3d *c, double d, int color)
{
	sphere->c = c;
	sphere->d = d;
	sphere->color = color;
}

// Possibly a universal function
double	get_min_pos_root(double disc, double a, double b)
{
	double	r1;
	double	r2;
	double	sqd;

	sqd = sqrt(disc);
	r1 = (-b + sqd) / (2 * a);
	r2 = (-b - sqd) / (2 * a);
	if (r1 >= 0 & r2 >= 0)
		return ((double)fmin(r1, r2));
	if (r1 > 0)
		return (r1);
	if (r2 > 0)
		return (r2);
	return ((double)NAN);
}

double 	sphere_intersect(t_sphere *sp, t_v3d *r, double *root)
{
	t_p3d	o_minus_c;
	double a;
	double b;
	double c;
	double d;
	double prod;

	init_p3d(&o_minus_c, 0, 0, 0);
	p_sub(&o_minus_c, &r->loc, sp->c);
	prod = dot(&r->dir, &o_minus_c);
	b = 2 * prod;
	a = dot(&r->dir, &r->dir);
	c = dot(&o_minus_c, &o_minus_c) - pow(sp->d/2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return ((double)(NAN));
	if (isnan((double)(*root = get_min_pos_root(d, a, b))))
		return ((double)NAN);
	return (*root);
}
void trace_sphere(t_conf *conf, double fov, t_sphere **sps, int n)
{
	t_v3d	ray;
	t_p3d	ipoint;
	int		i;
	int 	j;
	t_res	*res;
	double	mindist;
	t_sphere *minsp;
	double root;
	int k;

	i = 0;
	j = 0;
	k = 0;
	res = conf->res;
	ipoint.x = 0;
	ipoint.y = 0;
	ipoint.z = 0;
	mindist = (double)INFINITY;
	minsp = NULL;
	root = NAN;
	while (j < conf->res->Y)
	{
		i = 0;
		while (i < conf->res->X)
		{
			init_ray(&ray, res, i, j, fov);
			while (sps[k] != NULL)
			{
				if (!(isnan(sphere_intersect(*sps, &ray, &root))))
					if (root < mindist)
					{
						mindist = root;
						minsp = sps[k];
					}
				k++;
			}
			// if (i == 350 && j == 350)
			// 	printf("OK!\n");
			// if (ray.loc->z != 0)
			// 	printf("NOTOK\n");
			if (minsp != NULL)
			{
				my_mlx_pixel_put(conf->img, i, j, minsp->color);
				minsp = NULL;
			}
			k = 0;
			i++;
		}
	j++;
	}
}


int main()
{
	t_win	vars;
	t_res	res;
	t_data	img;

	t_conf	conf;
	t_args args;
	double fov;
	t_sphere sp;
	t_sphere sp2;
	t_sphere sp3;
	t_sphere *sps[4];

	sps[2] = &sp;
	sps[1] = &sp2;
	sps[0] = &sp3;
	sps[3] = NULL;


	char *test = "SPHERE!";

	// Window
	res.X = ft_atoi("700");
	res.Y = ft_atoi("700");
	conf = (t_conf){&img, &vars, &res};
	init_window(conf.vars, conf.res, test);
	init_img(conf.img, conf.vars, conf.res->X, conf.res->Y);
	
	// Infobar
	args.outwin = init_infobar(conf.vars->mlx, 210, 210, "RGB");
	args.conf = &conf;

	// Trace sphere Sphere
	init_sphere(&sp3, &(t_p3d){0, 0, 20}, 40, magenta);
	// init_sphere(&sp, &(t_p3d){0, 0, 100}, 20, white);
	// init_sphere(&sp2, &(t_p3d){0, 0, 50}, 6, green);
	fov = 180;
	trace_sphere(&conf, fov, sps, 1);
	// trace_sphere(&conf, &sp3, fov, 3);
	// trace_sphere(&conf, &sp, fov);
	

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_win, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_hook(args.outwin, DestroyNotify, StructureNotifyMask, close_win, &args);
	mlx_loop(vars.mlx);
}
