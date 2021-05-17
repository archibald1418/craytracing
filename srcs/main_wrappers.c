#include "minirt.h"

void	do_parser(char *path, t_rt *rt)
{
	int	out;

	if (!has_extension(path, ".rt"))
		handle_errors("Bad file extension");
	out = parser(path, rt);
	if (out == -1)
		handle_errors("Malloc error");
	if (out != 1)
		handle_errors("Parser error...");
}

void	do_bmp(int argc, char **argv, t_norm *norm)
{
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		if (save_bmp(&norm->conf) != 1)
			handle_errors("BMP error...");
		printf("Screenshot is ready\n");
		exit(0);
	}
}
