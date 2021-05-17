#include "minirt.h"

ssize_t	render(t_conf *conf, t_rt *rt, t_cam cam)
{
	t_v3d	orient;
	int		color;
	t_point	p;
	t_ray	ray;
	int		rate;

	p.y = 0;
	rate = 1;
	color = black;
	while (p.y <= conf->res.Y - rate)
	{
		p.x = 0;
		while (p.x <= conf->res.X - rate)
		{
			init_ray(&ray, &conf->res, p, cam);
			color = trace_shapes(ray, rt->shapes, &orient);
			if (color != black)
				color = calc_lights(color, orient, rt, cam);
			my_mlx_pixel_put(&conf->img, p.x, p.y, color);
			p.x += rate;
		}
		p.y += rate;
	}
	return (1);
}
