#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"
//#include "get_next_line_bonus.h"
#include <stdio.h>
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35;1m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define DOLLAR GREEN"$" RESET

int	test_gnl(int fd, char *line)
{
	int i;
	printf(MAGENTA"\n********************************** ( fd %d ) *********************************"RESET"\n\n", fd);
	while ((i = get_next_line(fd, &line)) > 0)
	{

		printf("i = %d %s%s\n", i, line, DOLLAR);
		free(line);
	}
	if (fd > 0)
	{
		printf("i = %d %s%s\n", i, line, DOLLAR);
		free(line);
	}
	return (0);
}
int main()
{
	int fd[10];
	char *line = NULL;

	fd[0] = open("alphabet.txt", O_RDONLY);
	fd[1] = open("all_i_ask.txt", O_RDONLY);
	fd[2] = open("empty.txt", O_RDONLY);
	fd[3] = open("file.txt", O_RDONLY);
	fd[4] = open("fail.txt", O_RDONLY);
	fd[5] = open("christmas_tree.txt", O_RDONLY);

	for(int i = 0; i < 6; i++)
		test_gnl(fd[i], line);
	//while(1){}
	return (0);
}
