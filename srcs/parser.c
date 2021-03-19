#include "minirt.h"
#include "tests.h"

// z = l/2*30*P/180
/* 
1 - gnl loop 👌
2 - print non-empty lines loop 👌
3 - split non-empty lines loop
4 - fill struct on valid file loop
5 - map out possible errors
6 - fill struct and handle errors (+ add struct setter)
*/

#define SPACES "\v\t \r\f"

void	parser(char *path)
{
	char *line;
	int fd;
	int out;
	int i;
	char **arr;

	i = 1;
	fd = open(path, O_RDONLY);
	out = 1;
	while (out > 0)
	{
		if ((out = get_next_line(fd, &line)) > 0 && *line != '\0')
		{
			arr = ft_strsplit(line, SPACES);
			ft_putstrarr(arr, ft_count_words(line, SPACES));
			free_arr((void**)arr, ft_count_words(line, SPACES));
		}
		i++;
		free(line);
	}
	if (out >= 0)
		close(fd);
	else
		dprintf(1, "FILE ERROR...\n");
}