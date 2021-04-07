#include "minirt.h"

int main()
{
	t_ray ray;

	int i = 0;
	int w = 10;
	int h = 10;
	while (i < w * h)
	{
		init_ray(&ray, w, h, (int)(i % w), (int)(i/w), 60.0);
		printf("(%d,%d) -> ray:(\n.loc (%5.2f,%5.2f, %5.2f)\n.dir (%5.2f,%5.2f,%5.2f)\n\n", 
		i % w,
		i / w,
		ray.loc->x, ray.loc->y, ray.loc->z,
		ray.dir->x, ray.dir->y, ray.dir->z);
		i++;
	}
}






