#include "tests.h"

int main()
{
	int fd;
	int out;
	char *line;
	int i;

	i = 1;
	line = NULL;
	fd = open("/Users/ldonita/42cursus/minirt/1.rt", O_RDONLY);
	while ((out = get_next_line(fd, &line)) > 0)
	{
		printf("#%3d -> |%s|\n", i, line);
		free(line);
		i++;
	}
	if (out != -1)
	{
		printf("#%3d -> |%s|\n", i, line);
		free(line);
		close(fd);
	}
}
