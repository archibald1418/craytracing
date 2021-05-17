#include "minirt.h"

int	parse_camera(char *id, char **tokens, t_rt *rt)
{
	t_bilist	*camnode;
	t_cam		cam;

	if (ft_strncmp(id, (char *)CAM, ft_strlen(id)) == 0)
	{
		if (check_cam(tokens, &cam) != 1)
			return (handle_errors("CAMERA ERROR...\n"));
		camnode = ft_bilistnew(&cam, sizeof(t_cam));
		if (!(camnode))
			return (handle_errors("Malloc error...\n"));
		ft_bilist_append_back(&rt->cams, camnode);
	}
	return (0);
}

int	parse_lsrc(char *id, char **tokens, t_rt *rt)
{
	t_bilist	*lightnode;
	t_lsrc		lsrc;

	if (ft_strncmp(id, (char *)LS, ft_strlen(id)) == 0)
	{
		if (check_lsrc(tokens, &lsrc) != 1)
			return (handle_errors("\nLIGHT SOURCE ERROR...\n"));
		lightnode = ft_bilistnew(&lsrc, sizeof(t_lsrc));
		if (!(lightnode))
			return (handle_errors("Malloc error...\n"));
		ft_bilist_append_back(&rt->lsrcs, lightnode);
	}
	return (0);
}
