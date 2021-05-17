#include "minirt.h"

const char	*g_ids[] = {RES, AMB, CAM, LS, PL, SP, SQ, CY, TR, NULL};

static int	has_single_id(char **tokens)
{
	int	flags[IDLEN];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < IDLEN)
		flags[i++] = 0;
	while (tokens[j] != NULL)
	{
		i = 0;
		while (((char **)g_ids)[i] != NULL)
		{
			if (ft_strncmp(((char **)g_ids)[i], tokens[j], 2) == 0)
				flags[i] += 1;
			if (flags[i] > 1)
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	check_line(t_rt *rt, char **tokens)
{
	char		*id;

	id = tokens[0];
	if (!(is_in_arr(id, (char **)g_ids)) && ft_strncmp(id, "#", 1) != 0)
		return (handle_errors("BAD IDENTIFIER IN FILE"));
	if (!(has_single_id(tokens)))
		return (handle_errors("MORE THAN ONE IDENTIFIER IN LINE\n"));
	if (ft_strncmp(id, (char *)RES, ft_strlen((char *)id)) == 0)
		if (check_res(tokens, rt) != 1)
			return (handle_errors("RESOLUTION ERROR...\n"));
	if (ft_strncmp(id, (char *)AMB, ft_strlen((char *)AMB)) == 0)
		if (check_lamb(tokens, rt) != 1)
			return (handle_errors("\nAMBIENT LIGHT ERROR...\n"));
	parse_camera(id, tokens, rt);
	parse_lsrc(id, tokens, rt);
	parse_shapes(id, tokens, rt);
	return (1);
}

int	gnl_loop(int fd, t_rt *rt)
{
	char	*line;
	char	**tokens;
	int		out;

	out = 1;
	while (out > 0 && fd != -1)
	{
		out = get_next_line(fd, &line);
		if (out >= 0 && *line != '\0')
		{
			tokens = ft_strsplit(line, SPACES);
			if (check_line(rt, tokens) != 1)
			{
				free_arr((void **)tokens, ft_count_words(line, SPACES));
				clean_rt(rt);
				free(line);
				return (handle_errors("\nCONFIG ERROR\n"));
			}
			free_arr((void **)tokens, ft_count_words(line, SPACES));
		}
		free(line);
	}
	return (out);
}

int	parser(const char *path, t_rt *rt)
{
	int		fd;
	int		out;

	init_rt(rt);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (handle_errors("\nFILE ERROR...\n"));
	out = gnl_loop(fd, rt);
	close(fd);
	if (out == -1)
		return (handle_errors("\nFILE ERROR...\n"));
	return (1);
}
