#include "minirt.h"
#include "tests.h"

/*
Уравнение прямой, проходящей через две точки в R^3

(x - x1) / (x2 - x1) = (y - y1) / (y2 - y1) = (z - z1) / (z2 - z1) 
или
(x - x1)/ax = (y - y1)/ay = (z - z1)/az, где а - направляющий вектор прямой


*/

void	init_sphere(t_sphere *sphere, t_p3d c, double d, int color)
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
	r1 = -b + sqd;
	r2 = -b - sqd;
	if (r1 >= 0 && r2 >= 0)
		return (fmin(r1, r2));
	if (r1 >= 0)
		return (r1);
	if (r2 >= 0)
		return (r2);
	return ((double)NAN);
}

double	sphere_intersect(t_sphere *sp, t_ray *r)
{
	t_p3d	ray_to_c;
	double	prod;
	double	d;
	double	a;
	double	root;

	p_sub(&ray_to_c, r->loc, sp->c);
	prod = dot(r->dir, ray_to_c);
	d = pow(prod, 2) - (dot(ray_to_c, ray_to_c) - pow((double)(sp->d/2), 2));
	a = dot(r->dir, r->dir);
	if (d < 0)
		return ((double)NAN);
	if (isnan((double)(root = get_min_pos_root(d, a, prod))))
		return ((double)NAN);
	// scalmult(ipoint, r->dir, root);
	// p_add(ipoint, ipoint, r->loc);
	return (root);
}
void trace_sphere(t_conf *conf, t_sphere **sps, double fov)
{
	t_v3d	ray;
	t_p3d	ipoint;
	int		i;
	int 	j;
	t_res	*res;
	t_sphere *minsp;
	double mindist;
	double dist;
	int k;

	i = 0;
	j = 0;
	k = 0;
	res = &conf->res;
	// ipoint.x = 0;
	// ipoint.y = 0;
	// ipoint.z = 0;
	mindist = INFINITY;
	dist = INFINITY;
	minsp = NULL;
	t_cam cam = {(t_p3d){0, 0, 0}, (t_p3d){0, 0, 0}, 53};
	while (j < conf->res.Y)
	{
		i = 0;
		while (i < conf->res.X)
		{
			init_ray(&ray, res, i, j, cam);
			while (sps[k] != NULL)
			{
				if (!(isnan(dist = sphere_intersect(sps[k], ray))))
				{
					// if (i == res->X / 2 && j == res->Y / 2)
					// 	printf("RAYDIR -> (%f,%f,%f)\n", ray.dir.x, ray.dir.y, ray.dir.z);
					if (dist < mindist)
					{
						mindist = dist;
						minsp = sps[k];
					}
				}
				k++;
			}
			if (minsp != NULL)
			{
				// printf("color => %X; z = %.1f\n", minsp->color, minsp->c.z);
				my_mlx_pixel_put(&conf->img, i, j, minsp->color);
			}
			k = 0;
			mindist = INFINITY;
			minsp = NULL;
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
	t_sphere spwhite;
	t_sphere spgreen;
	t_sphere spmagenta;
	t_sphere	 spyellow;

	// Spheres
	t_sphere *sps[5];


	char *test = "SPHERE!";

	// Window
	res.X = ft_atoi("1000");
	res.Y = ft_atoi("1000");
	conf = (t_conf){img, vars, res};
	init_window(&conf.vars, &conf.res, test);
	init_img(&conf.img, &conf.vars, conf.res.X, conf.res.Y);
	
	// Infobar
	args.outwin = init_infobar(conf.vars.mlx, 210, 210, "RGB");
	args.conf = &conf;

	// Trace sphere Sphere
	init_sphere(&spwhite, (t_p3d){-1, 0, 20.5}, 15, green);
	init_sphere(&spgreen, (t_p3d){-1, 0, 29}, 25, purple);
	init_sphere(&spmagenta, (t_p3d){-1, 0, 10}, 5, yellow);
	// init_sphere(&spyellow, (t_p3d){0, 0, 150}, 4, yellow);

	// Fill array of spheres
	sps[2] = &spwhite;
	sps[0] = &spmagenta;
	sps[1] = &spgreen;
	sps[3] = NULL;
	sps[4] = NULL;

	fov = 66;
	trace_sphere(&conf, sps, fov);
	// trace_sphere(&conf, &sp2, fov);
	// trace_sphere(&conf, &sp3, fov);

	mlx_put_image_to_window(conf.vars.mlx, conf.vars.win, conf.img.img, 0, 0);
	mlx_key_hook(conf.vars.win, key_hook, &conf.vars);
	mlx_hook(conf.vars.win, DestroyNotify, StructureNotifyMask, close_win, &conf.vars);
	mlx_hook(conf.vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
	mlx_hook(args.outwin, DestroyNotify, StructureNotifyMask, close_win, &args);
	// printf("gss gave -> %d\n\n", mlx_get_screen_size(conf.img, &conf.res->X, &conf.res->Y));
	mlx_loop(conf.vars.mlx);
}
