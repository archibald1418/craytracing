int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
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

int		add_shade(int trgb, double shade)
{
	// return (create_trgb(shade, get_r(trgb), get_g(trgb), get_b(trgb)));
	// FIXME: (d)printf works only with fd

	// dprintf(1, "shade -> %X\n", ((int)(shade * 255)) << 24);
	// dprintf(1, "shade -> %X\n", ((int)(shade * 255)) << 24);
	// dprintf(1, "color + shade -> %X\n", ((trgb & 0xFFFFFF) | ((int)(shade * 255)) << 24));
	return ((trgb & 0xFFFFFF) | (((int)(shade * 255)) << 24));
}

int		get_opposite(int trgb)
{
	// Leave t alone
	return ((~trgb & 0xFFFFFF) | (trgb & 0xFF000000));
}