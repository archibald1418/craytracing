#include "tests.h"
#include <limits.h>

// Orig:

void	test_atof(void)
{
	char *s1 = "123.567";
	char *s2 = "";
	char *s3 = " 345.4 ass";
	char s4[100];
	char *s5 = "5e+6";

	// sprintf(s4, "      %f", FLT_MAX);

	printf("|%.10f|\n", FLT_EPSILON);
}

void	test_ft_atof(void)
{
	;
}


int main(int argc, char **argv)
{
	int i = 1;
	double out;
	while (i < 2)
	{
		if ((out = ft_atof(argv[i])) == EPSILON)
		{
			printf("FLOAT NOT CALCULABLE...\n");
			return (0);
		}
		printf("|%f|\n", ft_atof(argv[i++]));
	}
	// test_atof();

	// char *d1 = "-080098769.-0";
	// sprintf(d1, "%f", FLT_MAX);
	

	// dprintf(1, "|%f|\n", ft_atof(d1));

}