#include "tests.h"

// #define PATH	"/Users/ldonita/42cursus/minirt/1.rt"
#define PATH	"1.rt"

#define SPACES "\v\t \r\f"

void	del_cam(t_cam *node)
{
	;
}

void	print_cam(t_cam *cam, int i)
{
	printf("CAM%i :\n.loc=(%2.f, %2.f, %2.f)\n.dir=(%2.f, %2.f, %2.f)\nfov=%d\n\n",\
	i,
	cam->loc.x, cam->loc.y, cam->loc.z,\
	cam->dir.x, cam->dir.y, cam->dir.z,
	cam->fov);
}

void	print_cams(t_bilast *cams)
{
	t_bilist *node;
	int i;
	node = cams->head;
	i = 1;
	while (node)
	{
		print_cam((t_cam *)node->content, i);
		node = node->next;
		i++;
	}
}

void	print_cams_back(t_bilast *cams)
{
	t_bilist *node;
	int i;
	node = cams->tail;
	i = 0;
	while (node)
	{
		print_cam((t_cam *)node->content, i);
		node = node->prev;
		i++;
	}
}

void	print_rt(t_rt *rt)
{
	printf("RES : (%d x %d)\n", rt->res.X, rt->res.Y);
	printf("AMB : .lum=%.2f, .rgb=(%d,%d,%d)\n", \
	rt->lamb.lum,
	rt->lamb.col.r,
	rt->lamb.col.g,
	rt->lamb.col.b);
    print_cams(&rt->cams);
}

void	test_parser(void)
{
	t_rt rt;
	
	init_rt(&rt);
	if (parser(PATH, &rt) == 1)
		print_rt(&rt);
	
}

int main()
{
	test_parser();
	// sleep(200);
	// system("leaks parser");
}