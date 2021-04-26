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
	t_data	img;
	t_conf	conf;
	t_args	args;
	t_rt	rt;
	int		out;

	if (argc == 2)
	{
		// Parsing
		out = parser("1.rt", &rt);
		if (out == -1)
			return (handle_malloc());
			// TODO: one more time for the leaks

		if (out != 1)
			return (printf("Error...\n"));

		// Window
		conf.res = (t_res)rt.res;
		init_window(&conf.vars, &conf.res, "RT");
		init_img(&conf.img, &conf.vars, conf.res.X, conf.res.Y);
		
		// Infobar
		args.outwin = init_infobar(conf.vars.mlx, 210, 210, "RGB");
		args.conf = &conf;

		// Rendering (pushing to image)
		out = render(&conf, &rt);
		if (out != 1)
			return (printf("Render error...\n"));

		// Setup hooks
		mlx_put_image_to_window(conf.vars.mlx, conf.vars.win, conf.img.img, 0, 0);
		mlx_key_hook(conf.vars.win, key_hook, &conf.vars);
		mlx_hook(conf.vars.win, DestroyNotify, StructureNotifyMask, close_win, &conf.vars);
		mlx_hook(conf.vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &args);
		mlx_hook(args.outwin, DestroyNotify, StructureNotifyMask, close_win, &args);
		mlx_loop(conf.vars.mlx);
	}
	printf("podai fajl na vkhod dolbaeb!");
	return (0);
}