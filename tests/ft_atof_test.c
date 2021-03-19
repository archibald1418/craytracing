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

	printf("|%f|\n", atof(s5));
}

void	test_ft_atof(void)
{
	;
}

// int argc, char **argv
int main()
{
	// int i = 1;
	// while (i++ < 4)
	// 	test_atof();
	// 		// printf("|%f|\n", atof(argv[i++]));s

	char *d1 = "456.1234";

	dprintf(1, "|%f|\n", ft_atof(d1));

}