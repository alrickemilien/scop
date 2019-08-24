#include "scop.h"

static int				load_tga_image(
	t_tga *tga,
	FILE *stream)
{
	size_t	size;
	size_t	size_read;

	tga->buffer = NULL;
	size = tga->width * tga->height * 4;
	if (!(tga->buffer = (uint8_t*)malloc(sizeof(uint8_t) * size + 1)))
		return (-1);
	if ((size_read = fread(tga->buffer, 1, size, stream)) != size)
	{
		fprintf(stderr, "%ld has been read\n", size_read);
		return (-1);
	}
	return (0);
}

static void				fill_tga_image(t_tga *tga)
{
	size_t	x;
	size_t	y;
	size_t	i;
	size_t	z;

	x = 0;
	y = 0;
	z = (tga->height - 1) * tga->width * 4;
	i = 0;
	while (i < tga->width * tga->height)
	{
		if (x > tga->width - 1)
		{
			x = 0;
			z = (tga->height - (++y + 1)) * tga->width * 4;
		}
		tga->image[x + (y * tga->width)] = uint32_color(
				tga->buffer[z + (x * 4)],
				tga->buffer[z + (x * 4) + 3],
				tga->buffer[z + (x * 4) + 2],
				tga->buffer[z + (x * 4) + 1]);
		x++;
		i++;
	}
}

int						load_tga_file_error(
	const char *pathname,
	FILE *stream)
{
	fprintf(stderr, "Unable to load file %s\n", pathname);
	if (stream)
		fclose(stream);
	return (-1);
}

/*
** Load TGA file
*/

int						load_tga_file(
	t_tga *tga,
	const char *pathname)
{
	FILE	*stream;

	printf("Start loading tga file %s\n", pathname);
	memset(tga, 0, sizeof(t_tga));
	tga->path = strdup(pathname);
	if ((stream = fopen(pathname, "rb")) == NULL)
		return (load_tga_file_error(pathname, stream));
	if (fill_tga_header(tga, &tga->header, stream))
		return (load_tga_file_error(pathname, stream));
	if (tga->header.id_length != 0
		&& tga->header.color_map_type != 0
		&& tga->header.image_type != NON_COMPRESSED_TGA)
		return (load_tga_file_error(pathname, stream));
	tga->image = (uint32_t*)malloc(sizeof(uint32_t) * tga->width * tga->height);
	load_tga_image(tga, stream);
	tga->buffer = decode_tga(tga);
	fill_tga_image(tga);
	free(tga->buffer);
	fclose(stream);
	return (0);
}
