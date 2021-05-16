#include "minirt.h"

#define BMPHeaderSize 14
#define DIBHeaderSize 40
#define PixelDataOffset BMPHeaderSize + DIBHeaderSize // Headers size
#define PixelSize	4
// Combined bitmap headers size is 54


void	set_fileheader(t_res res, int fd)
{
	int filesize;
	unsigned char header[PixelDataOffset];
	ft_bzero(header, PixelDataOffset);
	filesize = PixelDataOffset + (PixelSize * res.X * res.Y);
	// BMP
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)filesize;
	header[3] = (unsigned char)(filesize >> 8);
	header[4] = (unsigned char)(filesize >> 16);
	header[5] = (unsigned char)(filesize >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	// DIB
	header[18] = (unsigned char)res.X;
	header[19] = (unsigned char)(res.X >> 8);
	header[20] = (unsigned char)(res.X >> 16);
	header[21] = (unsigned char)(res.X >> 24);
	header[22] = (unsigned char)res.Y;
	header[23] = (unsigned char)(res.Y >> 8);
	header[24] = (unsigned char)(res.Y >> 16);
	header[25] = (unsigned char)(res.Y >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	header[34] = (unsigned char)((filesize - PixelDataOffset));
	header[35] = (unsigned char)((filesize - PixelDataOffset) >> 8);
	header[36] = (unsigned char)((filesize - PixelDataOffset) >> 16);
	header[37] = (unsigned char)((filesize - PixelDataOffset) >> 24);
	write(fd, header, 54);
}

int save_bmp(t_conf *conf)
{
	int fd;
	int i;
	int j;
	// int pi;
	// unsigned char trgb[4]; 
	unsigned int color;
	// char *addr;
	fd = open("test.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);

	set_fileheader(conf->res, fd);
	// addr = conf->img.addr; // unsigned?
	j = conf->res.Y - 1;
	while (j != -1)
	{
		i = 0;
		while (i < conf->res.X)
		{
			// color = my_mlx_pixel_get(&conf->img, i, j);
			// trgb[3] = 0;
			// trgb[2] = get_r(color);
			// trgb[1] = get_g(color);
			// trgb[0] = get_b(color);
			color = my_mlx_pixel_get(&conf->img, i, j);
			write(fd, &color, 4);
			i++;
		}
		j--;
	}
	
	
	// TODO: copy image at data->addr left to right bottom to top (note bpp in data & mlx_get_addr formula)
	// write(fd, )
	close(fd);
	return (1);
}