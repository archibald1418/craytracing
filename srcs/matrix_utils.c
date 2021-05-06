#include "minirt.h"

double	**init_matrix(t_p3d X, t_p3d Y, t_p3d Z)
{
	double m[3][3];

	m[0][0] = X.x;
	m[0][1] = Y.x;
	m[0][2] = Z.x;

	m[1][0] = X.y;
	m[1][1] = Y.y;
	m[1][2] = Z.y;

	m[2][0] = X.z;
	m[2][1] = Y.z;
	m[2][2] = Z.z;

	return (m);
}

double  **get_unit_matrix(void)
{
    t_p3d X;
    t_p3d Y;
    t_p3d Z;

    X = (t_p3d){1, 0, 0};
    Y = (t_p3d){0, 1, 0};
    Z = (t_p3d){0, 0, 1};

    return (init_matrix(X, Y, Z));
}

t_p3d   mat_mult_vec(double m[3][3], t_p3d vec)
{
    t_p3d res;

    double x;
    double y;
    double z;

    x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z;
    y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z;
    z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z;

    res = init_p3d(&res, x, y, z);
    return (res);
}

double  **get_new_basis(t_p3d tmp, t_cam cam)
{
    t_p3d forward;
    t_p3d right;
    t_p3d up;

    tmp = normalize(&tmp, tmp);
    forward = cam.dir;
    right = cross(&tmp, tmp, forward);
    up = cross(&up, right, forward);

    return(init_matrix(right, up, forward));

}

double  **get_rotation(t_cam cam)
{
    t_p3d up;
    t_p3d tmp;
    double **res;

    up = (t_p3d){0, 1, 0};
    tmp = cross(&tmp, up, cam.dir);
    if (is_zero(tmp))
        res = get_unit_matrix();
    else
        res = get_new_basis(tmp, cam);
    return (res);
}