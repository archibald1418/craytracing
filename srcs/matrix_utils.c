#include "minirt.h"

t_matrix    init_matrix(t_p3d X, t_p3d Y, t_p3d Z)
{
	t_matrix m;

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

t_matrix    get_unit_matrix(void)
{
    t_p3d X;
    t_p3d Y;
    t_p3d Z;

    X = (t_p3d){1, 0, 0};
    Y = (t_p3d){0, 0, 1};
    Z = (t_p3d){0, 1, 0};

    return (init_matrix(X, Y, Z));
}

t_p3d       mat_mult_vec(t_matrix m, t_p3d vec)
{
    t_p3d res;

    double x;
    double y;
    double z;

    x = m.m[0][0] * vec.x + m.m[1][0] * vec.y + m.m[2][0] * vec.z;
    y = m.m[0][1] * vec.x + m.m[1][1] * vec.y + m.m[2][1] * vec.z;
    z = m.m[0][2] * vec.x + m.m[1][2] * vec.y + m.m[2][2] * vec.z;

    // printf("x=%f y=%f z=%f\n", x, y, z);
    res = init_p3d(&res, x, y, z);
    return (res);
}

t_matrix    get_new_basis(t_p3d tmp, t_cam cam)
{
    t_p3d forward;
    t_p3d right;
    t_p3d up;

    tmp = normalize(&tmp, tmp);
    forward = cam.dir;
    right = cross(&right, tmp, forward);
    up = cross(&up, right, forward);
    
    up = normalize(&up, up);
    forward = normalize(&forward, forward);
    right = normalize(&right, right);

    return(init_matrix(up, right, forward));

}

t_matrix    get_rotation(t_cam cam)
{
    t_p3d up;
    t_p3d tmp;
    t_matrix res;

    up = (t_p3d){0, 1, 0};
    tmp = cross(&tmp, up, cam.dir);
    if (is_not_zero(tmp))
        res = get_new_basis(tmp, cam);
    else
        res = get_unit_matrix();
    return (res);
}

