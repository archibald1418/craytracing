#include "minirt.h"

const char	*g_ids2[] = {RES, AMB, CAM, LS, PL, SP, SQ, CY, TR, NULL};

int	parse_shapes(char *id, char **tokens, t_rt *rt)
{
	if (is_in_arr(id, (char **)(g_ids2 + 4)))
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
	return (0);
}
