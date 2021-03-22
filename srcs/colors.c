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
	return ((trgb & (0xFF << 24)) >> t_offset);
}

int		get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> r_offset);
}

int		get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> g_offset);
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

	rnew = ((get_r(trgba) + get_r(trgbb))) / 2;
	gnew = ((get_g(trgba) + get_g(trgbb))) / 2;
	bnew = ((get_b(trgba) + get_b(trgbb))) / 2;
	// rnew = fmin((get_r(trgba) + get_r(trgbb)), 255) ;
	// gnew = fmin((get_g(trgba) + get_g(trgbb)), 255) ;
	// bnew = fmin((get_b(trgba) + get_b(trgbb)), 255) ;

	return (create_trgb(0, rnew, gnew, bnew));
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

	rnew = (get_r(trgb)) * lum;
	gnew = (get_g(trgb)) * lum;
	bnew = (get_b(trgb)) * lum;

	return (create_trgb(get_t(trgb), (int)rnew, (int)gnew, (int)bnew));
}

//TODO: gradients

unsigned int	lum_gradient(int trgb, int midpoints)
{
	;
	return (0);
}
