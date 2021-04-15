#include "tests.h"

// #define PATH	"/Users/ldonita/42cursus/minirt/1.rt"
#define PATH	"tests/check.rt"

#define SPACES "\v\t \r\f"

void	print_rt(t_rt *rt)
{
	printf("RES : (%d x %d)\n", rt->res.X, rt->res.Y);
	printf("AMB : .lum=%.2f, .rgb=(%d,%d,%d)\n", \
	rt->lamb.lum,
	rt->lamb.col.r,
	rt->lamb.col.g,
	rt->lamb.col.b);
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