#include "minirt.h"

int	add_shade(int trgb, double shade)
{
	return ((trgb & 0xFFFFFF) | (((int)(shade * 255)) << 24));
}

int	get_opposite(int trgb)
{
	return ((~trgb & 0xFFFFFF) | (trgb & 0xFF000000));
}
