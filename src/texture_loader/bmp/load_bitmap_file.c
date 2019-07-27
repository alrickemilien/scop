#include "scop.h"

/**
 * The first byte is 'B' (0x42), the second byte is 'M' (0x4D)
 * A little endian uint16_t would see this as 0x4D42 which is what you are reading.
 * Try the following instead for a endian independent solution.
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

void		fill_missing_image_size(t_bitmap *bmp)
{
	if ((int)bmp->dib_header.image_width < 0)
		bmp->dib_header.image_width = -bmp->dib_header.image_width;
	if ((int)bmp->dib_header.image_height < 0)
		bmp->dib_header.image_height = -bmp->dib_header.image_height;

	// This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
	bmp->size =  bmp->dib_header.image_size == 0 ?
		bmp->dib_header.image_width * bmp->dib_header.image_height * bmp->dib_header.bits_per_pixel
		: bmp->dib_header.image_size;

	printf("bmp->dib_header.image_width : %d\n", bmp->dib_header.image_width);
	printf("bmp->dib_header.image_height : %d\n", bmp->dib_header.image_height);
	printf("bmp->dib_header.image_size : %d\n", bmp->dib_header.image_size);

	printf("bmp->size : %ld\n", bmp->size);
}

int			load_bitmap_file(
	t_bitmap *bmp,
	const char *pathname)
{
	FILE	*stream;
	size_t	size_read;
	int		endian;
	int		bmp_endian;

	printf("Start loading bitmap file %s\n", pathname);

	memset(bmp, 0, sizeof(t_bitmap));

	bmp->path = strdup(pathname);

	stream = fopen(pathname, "rb");

	if (stream == NULL) {
		fprintf(stderr, "Unable to load file %s\n", pathname);
		return (-1);
	}

	if ((size_read = fread(&bmp->header, 1, sizeof(t_bmp_header), stream)) != sizeof(t_bmp_header))
	{
		fprintf(stderr, "%ld has been read\n", size_read);
		fclose(stream);
		return (-1);
	}

	endian = find_endian();
	bmp_endian = find_bmp_endian(bmp->header.type);

	printf("bmp_endian : %d\n", bmp_endian);

	// Check type
	// Check offset
	if (bmp_endian == -1 || bmp->header.data_offset > bmp->header.size)
	{
		fclose(stream);
		return (-1);
	}

	if (fread(&bmp->dib_header, 1, sizeof(t_bmp_dib_header), stream) != sizeof(t_bmp_dib_header))
	{
		fclose(stream);
		return (-1);
	}

	fill_missing_image_size(bmp);

	bmp->width = (size_t)bmp->dib_header.image_width;
	bmp->height = (size_t)bmp->dib_header.image_height;

	fseek(stream, bmp->header.data_offset, SEEK_SET);

	bmp->buffer = (uint8_t*)malloc(bmp->size * sizeof(uint8_t));

	printf("bmp->dib_header.bits_per_pixel : %d\n", bmp->dib_header.bits_per_pixel);

	size_read = fread(bmp->buffer, 1, bmp->size, stream);

	if (bmp->dib_header.image_size != 0
		&& size_read != bmp->size) {
		fprintf(stderr, "%ld has been read\n", size_read);
		free(bmp->buffer);
		bmp->buffer = NULL;
		fclose(stream);
		return (-1);
	}
	
	fclose(stream);

	return (0);
}
