#include "minirt.h"

double	calc_der(t_line *a)
{
	int dx;
	int dy;
	double res;

	dx = a->A->x - a->B->x;
	dy = a->A->y - a->B->y;	
	res = abs(dy/dx);
	return (res);	
}

void	put_text(t_conf *conf, char *str)
{
	mlx_string_put(conf->vars->mlx, conf->vars->win, 100, 100, white, str);
}



