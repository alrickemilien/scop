#include "scop.h"

static int			find_endian(void)
{
	int		s;
	char	*c;

	s = 1;
	c = (char*)&s;
	if (*c == 1)
		return (1);
	return (0);
}

static uint8_t		*decode_tga_little_endian(t_tga *tga, uint8_t *image)
{
	uint8_t	*end;
	uint8_t	*begin;
	uint8_t	argb[4];

	begin = image;
	end = image + (tga->width * tga->height * 4);
	while (image < end)
	{
		argb[0] = *(image + 0);
		argb[1] = *(image + 1);
		argb[2] = *(image + 2);
		argb[3] = *(image + 3);
		image[0] = argb[0];
		image[1] = argb[1];
		image[2] = argb[2];
		image[3] = argb[3];
		image += 4;
	}
	return (begin);
}

static uint8_t		*decode_tga_big_endian(t_tga *tga, uint8_t *image)
{
	uint8_t	*end;
	uint8_t	*begin;
	uint8_t	argb[4];

	begin = image;
	end = image + (tga->width * tga->height * 4);
	while (image < end)
	{
		argb[0] = *(image + 0);
		argb[1] = *(image + 1);
		argb[2] = *(image + 2);
		argb[3] = *(image + 3);
		image[3] = argb[0];
		image[2] = argb[1];
		image[1] = argb[2];
		image[0] = argb[3];
		image += 4;
	}
	return (begin);
}

uint8_t				*decode_tga(t_tga *tga)
{
	int	endian;

	endian = find_endian();
	return (endian == 0 ? decode_tga_little_endian(tga, tga->buffer)
		: decode_tga_big_endian(tga, tga->buffer));
}
