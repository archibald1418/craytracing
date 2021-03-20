#include "tests.h"

// #define PATH	"/Users/ldonita/42cursus/minirt/1.rt"
#define PATH	"check.rt"

#define SPACES "\v\t \r\f"

void	test_parser(void)
{
	t_rt rt;
	char *line1;
	char *line2;
	char **tokens1;
	char **tokens2;

	line1 = "R	 180 180";
	line2 = "A 		1	 78,2,5";

	tokens1 = ft_strsplit(line1, SPACES);
	tokens2 = ft_strsplit(line2, SPACES);

	ft_putstrarr(tokens1, ft_count_words(line1, SPACES));
	ft_putstrarr(tokens2, ft_count_words(line2, SPACES));

	// NOTE: we use init only if in need to validate fields in struct
	init_rt(&rt);

	// check_res(tokens1, &rt);
	check_lamb(tokens2, &rt);
	// parser(PATH);
	
}

int main()
{
	test_parser();
	// sleep(100);
}