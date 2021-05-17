// #include "tests.h"
#include "minirt.h"

int handle_errors(char *msg)
{
	printf("Error\n%s...\n", msg);
	exit(0);
	return (0);
}

int	has_extension(char *filename, char *ext)
{
	size_t len;
	len = ft_strlen(filename);
	if (len < ft_strlen(ext))
		return (0);
	if (ft_strcmp(&filename[len - 3], ext) != 0)
		return (0);
	return (1);
}

static void	setup_hooks(t_norm *norm)
{
	mlx_key_hook(norm->conf.vars.win, key_hook, norm);
	mlx_hook(norm->conf.vars.win, DestroyNotify, StructureNotifyMask, \
			close_win, &norm->conf.vars);
	mlx_hook(norm->conf.vars.win, MotionNotify, PointerMotionMask, \
			put_mouse_pos, &norm->args);
	mlx_hook(norm->args.outwin, DestroyNotify, StructureNotifyMask, \
			close_win, &norm->args.conf->vars);
	mlx_loop(norm->conf.vars.mlx);
}

int main(int argc, char **argv)
{
	t_norm	norm;

	if (argc >= 2)
	{
		do_parser(argv[1], &norm.rt);
		norm.conf.res = (t_res)norm.rt.res;
		init_window(&norm.conf.vars, &norm.conf.res, "RT");
		init_img(&norm.conf.img, &norm.conf.vars, \
		norm.conf.res.X, norm.conf.res.Y);
		do_render(&norm.conf, &norm.rt, (t_cam *)norm.rt.cams.head->content);
		norm.conf.node = norm.rt.cams.head;
		do_bmp(argc, argv, &norm);
		norm.args.outwin = init_infobar(norm.conf.vars.mlx, 210, 210, "RGB");
		norm.args.conf = &norm.conf;
		mlx_put_image_to_window(norm.conf.vars.mlx, norm.conf.vars.win, \
		norm.conf.img.img, 0, 0);
		setup_hooks(&norm);
	}
	else 
		return (handle_errors("No file on input..."));
	return (0);
}