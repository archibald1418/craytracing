#include "minirt.h"

#define R_OFFSET 16
#define G_OFFSET 8
#define B_OFFSET 0
#define T_OFFSET 24

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b << 0);
}

int	get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> T_OFFSET);
}

int	get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> R_OFFSET);
}

int	get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> G_OFFSET);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	get_rgb(int trgb)
{
	return (trgb & 0x00FFFFFF);
}

int	add_shade(int trgb, double shade)
{
	return ((trgb & 0xFFFFFF) | (((int)(shade * 255)) << 24));
}

int	get_opposite(int trgb)
{
	return ((~trgb & 0xFFFFFF) | (trgb & 0xFF000000));
}

int	t_min_max(int n, int min, int max)
{
	if (n < min)
		n = min;
	if (n > max)
		n = max;
	return (n);
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

int	subtr_trgb(int trgba, int trgbb)
{
	int	rnew;
	int	gnew;
	int	bnew;

	rnew = get_r(trgba) - get_r(trgbb);
	gnew = get_g(trgba) - get_g(trgbb);
	bnew = get_b(trgba) - get_b(trgbb);
	rnew *= (rnew >= 0);
	gnew *= (gnew >= 0);
	bnew *= (bnew >= 0);
	return (create_trgb(get_t(trgba), rnew, gnew, bnew));
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