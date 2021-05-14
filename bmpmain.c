#include "minirt.h"

#define PixelDataOffset 54
#define PixelSize	4
// Combined bitmap headers size is 54


void	set_fileheader(t_res res, int fd)
{
	int filesize;
	unsigned char header[PixelDataOffset];
	ft_bzero(header, PixelDataOffset);
	filesize = PixelDataOffset + (PixelSize * res.X * res.Y);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)filesize;
	header[3] = (unsigned char)(filesize >> 8);
	header[4] = (unsigned char)(filesize >> 16);
	header[5] = (unsigned char)(filesize >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
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
	write(fd, header, 54);
}

int main()
{	
	int fd;
	fd = open("test.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);

	set_fileheader((t_res){10,10}, fd);
	// TODO: join raytracer with this crap
	close(fd);
	return (0);
}