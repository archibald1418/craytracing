// #include "tests.h"
#include "minirt.h"

int	handle_malloc(void)
{
	perror("Error\nMalloc error\n");
	exit(0);
	return (-1);
}

int main(int argc, char **argv)
{
	t_norm	norm;
	int		out;

	if (argc == 2)
	{
		// Parsing
		out = parser(argv[1], &norm.rt);
		if (out == -1)
			return (handle_malloc());
			// TODO: one more time for the leaks

		if (out != 1)
			return (printf("Error...\n"));

		// Window
		norm.conf.res = (t_res)norm.rt.res;
		init_window(&norm.conf.vars, &norm.conf.res, "RT");
		init_img(&norm.conf.img, &norm.conf.vars, norm.conf.res.X, norm.conf.res.Y);
		
		// Infobar
		norm.args.outwin = init_infobar(norm.conf.vars.mlx, 210, 210, "RGB");
		norm.args.conf = &norm.conf;

		// Rendering (pushing to image)
		out = render(&norm.conf, &norm.rt, *(t_cam *)norm.rt.cams.head->content);
		norm.conf.node = norm.rt.cams.head;
		if (out != 1)
			return (printf("Render error...\n"));

		// Setup hooks
		mlx_put_image_to_window(norm.conf.vars.mlx, norm.conf.vars.win, norm.conf.img.img, 0, 0);
		mlx_key_hook(norm.conf.vars.win, key_hook, &norm);
		mlx_hook(norm.conf.vars.win, DestroyNotify, StructureNotifyMask, close_win, &norm.conf.vars);
		mlx_hook(norm.conf.vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &norm.args);
		mlx_hook(norm.args.outwin, DestroyNotify, StructureNotifyMask, close_win, &norm.args);
		mlx_loop(norm.conf.vars.mlx);
	}
	printf("\nPODAI FAIL NA VKHOD DOLBAEB!\n");
	return (0);
}