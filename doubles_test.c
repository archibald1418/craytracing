#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	double ratio = drand48();
	double alpha = ratio * 255;

	int i = 0;
	while (i < 20)
	{
		printf("ratio -> %f\talpha -> %f\n", ratio, alpha);
		i++;
		ratio = drand48();
		alpha = ratio * 255;
	}

	
}