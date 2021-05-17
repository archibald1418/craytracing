#include "minirt.h"

t_matrix	init_matrix(t_p3d X, t_p3d Y, t_p3d Z)
{
	t_matrix	m;

	m.m[0][0] = X.x;
	m.m[0][1] = Y.x;
	m.m[0][2] = Z.x;
	m.m[1][0] = X.y;
	m.m[1][1] = Y.y;
	m.m[1][2] = Z.y;
	m.m[2][0] = X.z;
	m.m[2][1] = Y.z;
	m.m[2][2] = Z.z;
	return (m);
}

t_matrix	get_unit_matrix(void)
{
	t_p3d	X;
	t_p3d	Y;
	t_p3d	Z;

	X = (t_p3d){1, 0, 0};
	Y = (t_p3d){0, 0, 1};
	Z = (t_p3d){0, 1, 0};
	return (init_matrix(X, Y, Z));
}

t_p3d	mat_mult_vec(t_matrix m, t_p3d vec)
{
	t_p3d	res;
	double	x;
	double	y;
	double	z;

	x = m.m[0][0] * vec.x + m.m[1][0] * vec.y + m.m[2][0] * vec.z;
	y = m.m[0][1] * vec.x + m.m[1][1] * vec.y + m.m[2][1] * vec.z;
	z = m.m[0][2] * vec.x + m.m[1][2] * vec.y + m.m[2][2] * vec.z;
	res = init_p3d(&res, x, y, z);
	return (res);
}

t_p3d	get_up(t_cam cam)
{
	t_p3d	up;

	up = (t_p3d){0, 1, 0};
	if (cam.dir.x == 0 && \
		cam.dir.y == 1 && \
		cam.dir.z == 0)
		up = (t_p3d){0, 0, -1};
	if (cam.dir.x == 0 && \
		cam.dir.y == -1 && \
		cam.dir.z == 0)
		up = (t_p3d){0, 0, 1};
	return (up);
}

t_p3d	rot_ray(t_cam cam, t_ray ray)
{
	t_p3d	up;
	t_p3d	right;
	t_p3d	forward;
	t_p3d	res;
	t_p3d	tmp;

	tmp = get_up(cam);
	forward = cam.dir;
	cross(&right, tmp, forward);
	normalize(&right, right);
	cross(&up, right, forward);
	normalize(&up, up);
	res.x = ray.dir.x * right.x + \
			ray.dir.y * up.x + \
			ray.dir.z * forward.x;
	res.y = ray.dir.x * right.y + \
			ray.dir.y * up.y + \
			ray.dir.z * forward.y;
	res.z = ray.dir.x * right.z + \
			ray.dir.y * up.z + \
			ray.dir.z * forward.z;
	normalize(&res, res);
	return (res);
}
