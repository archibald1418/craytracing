#include "libft.h"
#include "tests.h"


#define BIBLE "bible.txt"
#define WAR "war_and_peace_test.txt"

int main(int argc, char **argv)
{
	 (void)argc;
	char *line;
	// char buf[300];
	int i = 1;
	int out = 0;

	int fd = open(argv[1], O_RDONLY);
//	while (1)
//	{
//		out = get_next_line(fd, &line);
//		if (out != -1)
//            if (out != 0)
//            {
//                printf("|%s|", line);
//                free(line);
//            }
//			else
//				break;
//		else {
//			printf("ERROR OCCURED, gnl returned -1\n");
//			return (-1);
//		}
//		i++;
//		printf("\n");
//	}
//	if (fd > -1)
//		close(fd);
    while ((out = get_next_line(fd, &line)) > 0)
    {
        printf("|%s| -> %d\n", line, out);
        free(line);
    }
	printf("|%s| -> %d\n", line, out);
	free(line);
	return (0);
}
