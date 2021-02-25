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

	// TODO: bits is better but how?...
	rnew = (get_r(trgba) + get_r(trgbb)) % 256;
	gnew = (get_g(trgba) + get_g(trgbb)) % 256;
	bnew = (get_b(trgba) + get_b(trgbb)) % 256;

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

	rnew = (int)((double)get_r(trgb) * lum);
	gnew = (int)((double)get_g(trgb) * lum);
	bnew = (int)((double)get_b(trgb) * lum);

	return (create_trgb(get_t(trgb), rnew, gnew, bnew));
}

//TODO: gradients