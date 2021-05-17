#include "minirt.h"

void	init_rt(t_rt *rt)
{
	rt->res = (t_res){0, 0};
	rt->lamb = (t_lamb){0, (t_color){0, 0, 0}};
	ft_bzero(rt->shapes.shapes, sizeof(t_shape) * (MAX_SHAPES + 1));
	rt->lsrcs.head = NULL;
	rt->lsrcs.tail = NULL;
	rt->cams.head = NULL;
	rt->cams.tail = NULL;
	rt->shapes.top = 0;
}

void	clean_rt(t_rt *rt)
{
	int	j;

	j = 0;
	ft_bilistclear(&(rt->cams.head), free);
	ft_bilistclear(&(rt->lsrcs.head), free);
	while (rt->shapes.shapes[j].shape != NULL)
		free(rt->shapes.shapes[j++].shape);
}
