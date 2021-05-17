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

double	det3(t_matrix m)
{
	return (
		m.m[0][0] * m.m[1][1] * m.m[2][2] - \
		m.m[0][0] * m.m[1][2] * m.m[2][1] - \
		m.m[0][1] * m.m[1][0] * m.m[2][2] + \
		m.m[0][1] * m.m[1][2] * m.m[2][0] + \
		m.m[0][2] * m.m[1][0] * m.m[2][1] - \
		m.m[0][2] * m.m[1][1] * m.m[2][0]
	);
}

t_matrix	get_inverse(t_matrix m)
{
	double	det;
	double	inv_det;
	t_p3d	i;
	t_p3d	j;
	t_p3d	k;

	det = det3(m);
	inv_det = pow(det, -1);
	i = (t_p3d){m.m[0][0], m.m[0][1], m.m[0][2]};
	j = (t_p3d){m.m[1][0], m.m[1][1], m.m[1][2]};
	k = (t_p3d){m.m[2][0], m.m[2][1], m.m[2][2]};
	scalmult(&i, i, inv_det);
	scalmult(&j, j, inv_det);
	scalmult(&k, k, inv_det);
	return (init_matrix(i, j, k));
}

t_matrix	get_new_basis(t_p3d up, t_cam cam)
{
	t_p3d		forward;
	t_p3d		right;
	t_p3d		tmp;
	t_matrix	basis;

	tmp = normalize(&tmp, up);
	forward = cam.dir;
	right = cross(&right, tmp, forward);
	up = cross(&up, forward, right);
	up = normalize(&up, up);
	forward = normalize(&forward, forward);
	right = normalize(&right, right);
	basis = init_matrix(up, right, forward);
	return (init_matrix(up, right, forward));
}

t_matrix	get_rotation(t_cam cam)
{
	t_p3d		up;
	t_p3d		right;
	t_p3d		forward;
	t_matrix	res;

	up = (t_p3d){0, 1, 0};
	if (!is_not_zero(cross(&up, cam.dir, up)))
		res = get_unit_matrix();
	else
	{
		up = (t_p3d){0, 1, 0};
		cross(&right, cam.dir, up);
		cross(&up, cam.dir, right);
		forward = cam.dir;
		res = get_new_basis(up, cam);
	}
	return (res);
}

t_matrix	get_rot_x(t_cam cam)
{
	t_p3d	i;
	t_p3d	j;
	t_p3d	k;

	i = (t_p3d){1, 0, 0};
	j = (t_p3d){0, cam.dir.y, -cam.dir.z};
	k = (t_p3d){0, cam.dir.z, cam.dir.y};
	return (init_matrix(i, j, k));
}

t_matrix	get_rot_y(t_cam cam)
{
	t_p3d	i;
	t_p3d	j;
	t_p3d	k;

	i = (t_p3d){cam.dir.x, 0, cam.dir.z};
	j = (t_p3d){0, 1, 0};
	k = (t_p3d){-cam.dir.z, 0, cam.dir.x};
	return (init_matrix(i, j, k));
}

t_matrix	get_rot_z(t_cam cam)
{
	t_p3d	i;
	t_p3d	j;
	t_p3d	k;

	i = (t_p3d){cam.dir.x, -cam.dir.y, 0};
	j = (t_p3d){cam.dir.y, cam.dir.x, 0};
	k = (t_p3d){0, 0, 1};
	return (init_matrix(i, j, k));
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
