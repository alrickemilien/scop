/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bitmap_file_header.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:29:31 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:31:39 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** The first byte is 'B' (0x42), the second byte is 'M' (0x4D)
** A little endian uint16_t would see this as 0x4D42.
** Try the following instead for a endian independent solution.
*/

static int	find_bmp_endian(uint8_t type[2])
{
	if (type[0] == 0x42 && type[1] == 0x4D)
		return (1);
	if (type[0] == 0x4D && type[1] == 0x42)
		return (0);
	return (-1);
}

static int	find_endian(void)
{
	int		s;
	char	*c;

	s = 1;
	c = (char*)&s;
	if (*c == 1)
		return (1);
	return (0);
}

static void	debug_bitmap_header(t_bitmap *bmp)
{
	printf("bmp->dib_header.image_width : %d\n"
		"bmp->dib_header.image_height : %d\n"
		"bmp->dib_header.image_size : %d\n"
		"bmp->size : %ld\n",
		bmp->dib_header.image_width,
		bmp->dib_header.image_height,
		bmp->dib_header.image_size,
		bmp->size);
}

/*
** This is the size of the raw bitmap data;
** a dummy 0 can be given for BI_RGB bitmaps.
*/

void		fill_missing_image_size(t_bitmap *bmp)
{
	if ((int)bmp->dib_header.image_width < 0)
		bmp->dib_header.image_width = -bmp->dib_header.image_width;
	if ((int)bmp->dib_header.image_height < 0)
		bmp->dib_header.image_height = -bmp->dib_header.image_height;
	bmp->size = bmp->dib_header.image_size == 0
		? bmp->dib_header.image_width
			* bmp->dib_header.image_height
			* bmp->dib_header.bits_per_pixel
		: bmp->dib_header.image_size;
	(void)debug_bitmap_header;
}

int			load_bitmap_file_header(
	t_bitmap *bmp,
	FILE *stream)
{
	size_t	size_read;
	int		endian;
	int		bmp_endian;

	if ((size_read = fread(&bmp->header, 1,
		sizeof(t_bmp_header), stream)) != sizeof(t_bmp_header))
		return (-1);
	endian = find_endian();
	bmp_endian = find_bmp_endian(bmp->header.type);
	if (bmp_endian == -1 || bmp->header.data_offset > bmp->header.size)
		return (-1);
	if (fread(&bmp->dib_header, 1,
		sizeof(t_bmp_dib_header), stream) != sizeof(t_bmp_dib_header))
		return (-1);
	fill_missing_image_size(bmp);
	bmp->width = (size_t)bmp->dib_header.image_width;
	bmp->height = (size_t)bmp->dib_header.image_height;
	return (0);
}
