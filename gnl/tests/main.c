#include "get_next_line.h"

// void    ft_putstring(t_string *string)
// {
//     write(1, string->text, string->len);
// }



int main()
{
	char *line;

	int fd = open("tests/test.txt", O_RDONLY);

	// gnl reads & writes to line

	int i = 4;
	while (i--)
	{
		get_next_line (fd, &line);
		printf(">>>line is now\n'%s'", line); 
	}
	if (fd > -1)
		close(fd);
	free(line); // malloc for line in gnl
}

