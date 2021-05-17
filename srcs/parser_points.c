#include "minirt.h"

void	parse_location(char ***ploc, t_p3d *loc, char **tokens)
{
	*ploc = ft_strsplit(tokens[1], ",");
	if (!(*ploc))
		handle_errors("Malloc error...\n");
	if (check_point(ploc, loc, 0) != 1)
		handle_errors("LOCATION ERROR ¯\\_(ツ)_/¯\n");
}

void	parse_direction(char ***pdir, t_p3d *dir2, char **tokens)
{
	*pdir = ft_strsplit(tokens[2], ",");
	if (!(*pdir))
		handle_errors("Malloc error...\n");
	if (check_point(pdir, dir2, 1) != 1)
		handle_errors("DIRECTION ERROR ¯\\_(ツ)_/¯\n");
}

int	parse_posdir(char **tokens, t_p3d *l, t_p3d *d, char *type)
{
	char	**ploc;
	char	**pdir;

	(void)type;
	parse_location(&ploc, l, tokens);
	if (d != NULL)
		parse_direction(&pdir, d, tokens);
	return (1);
}
