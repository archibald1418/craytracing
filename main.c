// #include "tests.h"
#include "minirt.h"

int	handle_malloc(void)
{
	perror("Error\nMalloc error\n");
	exit(0);
	return (-1);
}

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

int	exit_cleanly(t_rt *rt, char *msg)
{
	clean_rt(rt);
	printf("Error\n%s\n", msg);
	exit(0);
}

int main(int argc, char **argv)
{
	t_norm	norm;
	int		out;

	if (argc >= 2)
	{
		// Check file extension
		if (!has_extension(argv[1], ".rt"))
			return (handle_errors("Bad file extension"));

		// Parsing
		out = parser(argv[1], &norm.rt);
		if (out == -1)
			return (handle_errors("Malloc error"));
		if (out != 1)
			return (handle_errors("Parser error..."));

		// Init an image
		norm.conf.res = (t_res)norm.rt.res;
		// Window
		init_window(&norm.conf.vars, &norm.conf.res, "RT");
		init_img(&norm.conf.img, &norm.conf.vars, norm.conf.res.X, norm.conf.res.Y);

		// Rendering (pushing to image)
		out = render(&norm.conf, &norm.rt, *(t_cam *)norm.rt.cams.head->content);
		norm.conf.node = norm.rt.cams.head;
		if (out != 1)
			return (handle_errors("Render error..."));
		if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
			if (save_bmp(&norm.conf) != 1)
				return (handle_errors("BMP error..."));
		// Setting up a window
		
		// Infobar
		norm.args.outwin = init_infobar(norm.conf.vars.mlx, 210, 210, "RGB");
		norm.args.conf = &norm.conf;
			
		// Setup hooks
		mlx_put_image_to_window(norm.conf.vars.mlx, norm.conf.vars.win, norm.conf.img.img, 0, 0);
		mlx_key_hook(norm.conf.vars.win, key_hook, &norm);
		mlx_hook(norm.conf.vars.win, DestroyNotify, StructureNotifyMask, close_win, &norm.conf.vars);
		mlx_hook(norm.conf.vars.win, MotionNotify, PointerMotionMask, put_mouse_pos, &norm.args);
		mlx_hook(norm.args.outwin, DestroyNotify, StructureNotifyMask, close_win, &norm.args.conf->vars);
		mlx_loop(norm.conf.vars.mlx);
	}
	else 
		return (handle_errors("No file on input..."));
	return (0);
}