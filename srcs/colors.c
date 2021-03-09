#include "minirt.h"

#define r_offset 16
#define g_offset 8
#define b_offset 0
#define t_offset 24

int		create_trgb(int t, int r, int g, int b)
{
		
	return(t << 24 | r << 16 | g << 8 | b << 0);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		get_rgb(int trgb)
{
	return (trgb & 0x00FFFFFF);
}

int		add_shade(int trgb, double shade)
{
	return ((trgb & 0xFFFFFF) | (((int)(shade * 255)) << 24));
}

int		get_opposite(int trgb)
{
	return ((~trgb & 0xFFFFFF) | (trgb & 0xFF000000));
}

int		add_trgb(int trgba, int trgbb)
{
	int rnew;
	int gnew;
	int bnew;

	rnew = ((get_r(trgba) + get_r(trgbb)) >> r_offset) / 2;
	gnew = ((get_g(trgba) + get_g(trgbb)) >> g_offset) / 2;
	bnew = ((get_b(trgba) + get_b(trgbb)) >> b_offset) / 2;

	return (create_trgb(get_t(trgba), rnew, gnew, bnew));
}

int		subtr_trgb(int trgba, int trgbb)
{
	int rnew;
	int gnew;
	int bnew;

	rnew = get_r(trgba) - get_r(trgbb);
	gnew = get_g(trgba) - get_g(trgbb);
	bnew = get_b(trgba) - get_b(trgbb);

	rnew *= (rnew >= 0);
	gnew *= (gnew >= 0);
	bnew *= (bnew >= 0);

	return (create_trgb(get_t(trgba), rnew, gnew, bnew));
}

int		set_lum(int trgb, double lum)
{
	int rnew;
	int gnew;
	int bnew;

	rnew = (double)((int)(get_r(trgb)) >> r_offset) * lum;
	gnew = (double)((int)(get_g(trgb)) >> g_offset) * lum;
	bnew = (double)((int)(get_b(trgb)) >> b_offset) * lum;

	return (create_trgb(get_t(trgb), rnew, gnew, bnew));
}

//TODO: gradients

int main()
{
	dprintf(1, "cyan rgb ->%d\n", 0x00FFFF);
	dprintf(1, "yellow rdb ->%d\n", 0xFFFF00);

	dprintf(1, "yellow + cyan\n =\n%d\n", add_trgb(0x00FFFF, 0xFFFF00));
}