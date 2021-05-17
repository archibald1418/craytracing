#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b << 0);
}

int	add_trgb(int trgba, int trgbb, double n)
{
	double	rnew;
	double	gnew;
	double	bnew;

	rnew = t_min_max(n / 255 * get_r(trgba) * get_r(trgbb), 0, 255);
	gnew = t_min_max(n / 255 * get_g(trgba) * get_g(trgbb), 0, 255);
	bnew = t_min_max(n / 255 * get_b(trgba) * get_b(trgbb), 0, 255);
	return (create_trgb(0, (int)rnew, (int)gnew, (int)bnew));
}

int	set_lum(int trgb, double lum)
{
	double	rnew;
	double	gnew;
	double	bnew;

	rnew = (get_r(trgb)) * lum;
	gnew = (get_g(trgb)) * lum;
	bnew = (get_b(trgb)) * lum;
	return (create_trgb(0, (int)rnew, (int)gnew, (int)bnew));
}

int	get_hex(t_color color)
{
	return (create_trgb(0, color.r, color.g, color.b));
}
