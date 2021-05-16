#include "minirt.h"

#define BMPHEADERSIZE 14
#define DIBHEADERSIZE 40
#define PIXELDATAOFFSET 54 // Headers size
// Combined bitmap headers size is 54
#define PIXELSIZE	4

void	write_bits(int num, unsigned char *addr)
{
	unsigned char bits[4];

	bits[0] = (unsigned char)num;
	bits[1] = (unsigned char)(num >> 8);
	bits[2] = (unsigned char)(num >> 16);
	bits[3] = (unsigned char)(num >> 24);
	ft_memcpy(addr, bits, 4);
}

void	set_fileheader(t_res res, int fd)
{
	int				filesize;
	unsigned char	header[PIXELDATAOFFSET];

	ft_bzero(header, PIXELDATAOFFSET);
	filesize = PIXELDATAOFFSET + (PIXELSIZE * res.X * res.Y);
	ft_memcpy(header, "BM", 2);
	write_bits(filesize, &header[2]);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	write_bits(res.X, &header[18]);
	write_bits(res.Y, &header[22]);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write_bits(filesize - PIXELDATAOFFSET, &header[34]);
	write(fd, header, 54);
}

int save_bmp(t_conf *conf)
{
	int fd;
	int i;
	int j;
	unsigned int color;
	fd = open("test.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);
	set_fileheader(conf->res, fd);
	j = conf->res.Y - 1;
	while (j != -1)
	{
		i = 0;
		while (i < conf->res.X)
		{
			color = my_mlx_pixel_get(&conf->img, i, j);
			write(fd, &color, 4);
			i++;
		}
		j--;
	}
	close(fd);
	return (1);
}