#include "minirt.h"

const char	*g_ids[] = {RES, AMB, CAM, LS, PL, SP, SQ, CY, TR, NULL};

void	init_rt(t_rt *rt)
{
	rt->res = (t_res){0, 0};
	rt->lamb = (t_lamb){0, (t_color){0, 0, 0}};
	ft_bzero(rt->shapes.shapes, sizeof(t_shape) * (MAX_SHAPES + 1));
	rt->lsrcs.head = NULL;
	rt->lsrcs.tail = NULL;
	rt->cams.head = NULL;
	rt->cams.tail = NULL;
	rt->shapes.top = 0;
}

void	clean_rt(t_rt *rt)
{
	int	j;

	j = 0;
	ft_bilistclear(&(rt->cams.head), free);
	ft_bilistclear(&(rt->lsrcs.head), free);
	while (rt->shapes.shapes[j].shape != NULL)
		free(rt->shapes.shapes[j++].shape);
}

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
	t_cam		cam;
	t_lsrc		lsrc;
	t_bilist	*camnode;
	t_bilist	*lightnode;

	id = tokens[0];
	// Parse set
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
	if (ft_strncmp(id, (char *)CAM, ft_strlen(id)) == 0)
	{
		if (check_cam(tokens, &cam) != 1)
			return (handle_errors("CAMERA ERROR...\n"));
		camnode = ft_bilistnew(&cam, sizeof(t_cam));
		if (!(camnode))
			return (handle_errors("Malloc error...\n"));
		ft_bilist_append_back(&rt->cams, camnode);
	}
	if (ft_strncmp(id, (char *)LS, ft_strlen(id)) == 0)
	{
		if (check_lsrc(tokens, &lsrc) != 1)
			return (handle_errors("\nLIGHT SOURCE ERROR...\n"));
		lightnode = ft_bilistnew(&lsrc, sizeof(t_lsrc));
		if (!(lightnode))
			return (-1);
		ft_bilist_append_back(&rt->lsrcs, lightnode);
	}
	// Parse shapes
	if (is_in_arr(id, (char **)(g_ids + 4)))
	{
		if (ft_strncmp(id, (char *)PL, ft_strlen((char *)PL)) == 0)
			if (check_pl(tokens, rt) != 1)
				return (handle_errors("PLANE ERROR..."));
		if (ft_strncmp(id, (char *)SP, ft_strlen(id)) == 0)
			if (check_sp(tokens, rt) != 1)
				return (handle_errors("SPHERE ERROR..."));
		if (ft_strncmp(id, (char *)SQ, ft_strlen((char *)SQ)) == 0)
			if (check_sq(tokens, rt) != 1)
				return (handle_errors("SQUARE ERROR..."));
		if (ft_strncmp(id, (char *)TR, ft_strlen((char *)TR)) == 0)
			if (check_tr(tokens, rt) != 1)
				return (handle_errors("TRIANGLE ERROR..."));
		if (ft_strncmp(id, (char *)CY, ft_strlen((char *)CY)) == 0)
			if (check_cy(tokens, rt) != 1)
				return (handle_errors("CYLINDER ERROR..."));
		rt->shapes.top++;
		if (rt->shapes.top > MAX_SHAPES)
			return (handle_errors("\n MAX SHAPES EXCEEDED. ABORT..."));
	}
	return (1);
}

int	parser(const char *path, t_rt *rt)
{
	char	*line;
	int		fd;
	int		out;
	int		i;
	char	**tokens;

	init_rt(rt);

	// GNL LOOP
	i = 1;
	fd = open(path, O_RDONLY);
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
				return (handle_errors("\nCONFIGU ERROR\n"));
			}
			free_arr((void **)tokens, ft_count_words(line, SPACES));
		}
		i++;
		free(line);
	}
	// Check gnl output
	if (out == 0 && fd != -1)
		close(fd);
	else
		return (handle_errors("\nFILE ERROR...\n"));
	return (1);
}
