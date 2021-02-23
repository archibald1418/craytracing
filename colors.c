int		set_color(int x, int a, int b)
{
	x = b ? (x > b) : x;
	x = a ? (x < a) : x;
	return (x);
}

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
	;
}

int		subtr_trgb(int trgba, int trgbb)
{
	;
}