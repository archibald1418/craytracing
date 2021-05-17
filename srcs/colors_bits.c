#include "minirt.h"

#define R_OFFSET 16
#define G_OFFSET 8
#define B_OFFSET 0
#define T_OFFSET 24

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
