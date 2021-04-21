#include "minirt.h"
// #include "tests.h"

// z = l/2*30*P/180
/* 
1 - gnl loop 👌
2 - print non-empty lines loop 👌
3 - split non-empty lines loop 👌
4 - fill struct on valid file loop
5 - map out possible errors
6 - fill struct and handle errors (+ add struct setter)
*/

#define SPACES "\v\t \r\f"

#define	RES		"R"
#define	AMB		"A"
#define	CAM		"c"
#define	LS		"l"
#define	PL		"pl"
#define	SP		"sp"
#define	SQ		"sq"
#define	CY		"cy"
#define TR		"tr"

#define IDLEN	9

const char *g_ids[] = {RES, AMB, CAM, LS, PL, SP, SQ, CY, TR, NULL};

/*

//
///
subj:
- Elements which are defined by a capital letter
 can only be declared once in the scene.

- Each element first’s information is the type identifier
 (composed by one or two character(s)),
  followed by all specific information for each object in a STRICT ORDER

- Each type of element CAN be separated by one or more line break(s).
-Each type of information from an element CAN be separated by one or more
space(s).

///

NOTE: Валиден ли такой инпут?:
R19201080A0.2255,255,255c-50,0,200,0,070
Вроде нет,потому что здесь нельзя ничего неоднозначно распарсить

Идем из допущения, что пробелы - разделитель между параметрами элемента сцены, 
а новые строки - между элементами сцены

//

RES: 2 positive numbers



*/

void	init_rt(t_rt *rt)
{
	rt->res		= (t_res){0, 0};
	rt->lamb	= (t_lamb){0, (t_color){0, 0, 0}};
	rt->shapes	= NULL;
	rt->lsrcs	= NULL;
	rt->cams.head = NULL;
	rt->cams.tail = NULL;
}

static int	has_single_id(char **tokens)
{
	int flags[IDLEN];
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < IDLEN)
		flags[i++] = 0;
	while (tokens[j] != NULL)
	{
		i = 0;
		while (((char**)g_ids)[i] != NULL)
		{
			if (ft_strncmp(((char**)g_ids)[i], tokens[j], 2) == 0)
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
	char *id;
	t_cam cam;
	t_bilist *camnode;

	id = tokens[0];
	if (!(is_in_arr(id, (char**)g_ids)))
		return (printf("IDENTIFIER '%s' IS NOT VALID\n", id));
	if (!(has_single_id(tokens)))
		return (printf("MORE THAN ONE IDENTIFIER IN LINE\n"));
	if (ft_strncmp(id, (char*)RES, ft_strlen((char*)RES)) == 0)
		if (check_res(tokens, rt) != 1)
			return (printf("RESOLUTION ERROR...\n"));
	if (ft_strncmp(id, (char*)AMB, ft_strlen((char*)AMB)) == 0)
		if (check_lamb(tokens, rt) != 1)
			return (printf("\nAMBIENT LIGHT ERROR...\n"));
	if (ft_strncmp(id, (char*)CAM, ft_strlen((char*)CAM)) == 0)
	{
		if (check_cam(tokens, &cam) != 1)
			return (printf("CAMERA ERROR...\n"));
		if (!(camnode = ft_bilistnew(&cam, sizeof(t_cam))))
			return (-1);
		ft_bilist_append_back(&rt->cams, camnode);
	}

	//TODO:
	/*
	check_cam : add to bilist
	check_lsrc
	check_sp
	check_pl
	check_tr
	check_sq
	check_cy
	*/
	return (1);

	
}

int		parser(const char *path, t_rt *rt)
{
	char	*line;
	int		fd;
	int		out;
	int		i;
	char	**tokens;

	init_rt(rt);
	i = 1;
	fd = open(path, O_RDONLY);
	out = 1;
	while (out > 0)
	{
		if ((out = get_next_line(fd, &line)) >= 0 && *line != '\0')
		{
			tokens = ft_strsplit(line, SPACES);
			if (check_line(rt, tokens) != 1)
			{
				free(line);
				return (printf("\nCONFIGURATION ERROR. TRY ANOTHER FILE\n"));
			}
			free_arr((void**)tokens, ft_count_words(line, SPACES));
		}
		i++;
		free(line);
	}
	if (out == 0)
		close(fd);
	else
		return(printf("\nFILE ERROR...\n"));
	return (1);
}