#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "colors.h"
#include <math.h>




int main()
{
	double ratio = drand48();
	double alpha = ratio * 255;

	int i = 0;
	while (i < 20)
	{
		printf("ratio -> %f\talpha -> %f\t->\t%d\n", ratio, alpha, (int)alpha);
		i++;
		ratio = drand48();
		alpha = ratio * 255;
	}
}