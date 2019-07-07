#include "scop.h"

static int				fill_tga_header(t_tga_header *header, FILE *stream)
{
	uint8_t				buff[18];
	size_t				i;
	size_t				size_read;

	if ((size_read = fread(header, 1, 18, stream)) != 18)
	{
		fprintf(stderr, "%ld has been read\n", size_read);
		return (-1);
	}

	header->id_length = buff[0];
	header->color_map_type = buff[1];
	header->image_type = buff[2];
	i = 2;
	while (i < 18)
	{
		if (i < 8)
			header->color_map_spec[i - 3] = buff[i];
		else
			header->image_spec[i - 8] = buff[i];
		i++;
	}
	return (0);
}

static void				fill_tga_size(t_tga_header *header)
{
	uint8_t	x[2];
	uint8_t	y[2];

	x[0] = header->image_spec[0x4];
	x[1] = header->image_spec[0x5];
	y[0] = header->image_spec[0x6];
	y[1] = header->image_spec[0x7];
	header->x = *(short*)x;
	header->y = *(short*)y;
}

static int	load_tga_image(t_tga *tga, FILE *stream)
{
	size_t			size;
	size_t			size_read;

	tga->buffer = NULL;
	size = tga->header.x * tga->header.y * 4;
	
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
	z = ((tga->header.y - 1) * tga->header.x) * 4;
	i = 0;
	while (i < (size_t)((tga->header.x * tga->header.y)))
	{
		if (x > (size_t)(tga->header.x - 1))
		{
			x = 0;
			y++;
			z = ((tga->header.y - (y + 1)) * tga->header.x) * 4;
		}

		tga->image[x + (y * tga->width)] = uint32_color(
				tga->buffer[z + (x * 4)],
				tga->buffer[z + (x * 4) + 3],
				tga->buffer[z + (x * 4) + 2],
				tga->buffer[z + (x * 4) + 1]
		);
		
		x++;
		i++;
	}
}

/**
 * 
 */
int				load_tga_file(
	t_tga *tga,
	const char *pathname)
{
	FILE				*stream;

	printf("Start loading tga file %s\n", pathname);

	memset(tga, 0, sizeof(t_tga));

	tga->path = strdup(pathname);
		
	stream = fopen(pathname, "rb");

	if (stream == NULL)
	{
		fprintf(stderr, "Unable to load file %s\n", pathname);
		return (-1);
	}

	if (fill_tga_header(&tga->header, stream))
	{
		fclose(stream);
		return (-1);
	}

	if (tga->header.id_length != 0
		&& tga->header.color_map_type != 0
		&& tga->header.image_type != NON_COMPRESSED_TGA)
	{
		fclose(stream);
		return (-1);
	}

	tga->width = (size_t)tga->header.x;
	tga->height = (size_t)tga->header.y;
	tga->image = (uint32_t*)malloc(sizeof(uint32_t) * tga->width * tga->height);

	fill_tga_size(&tga->header);

	load_tga_image(tga, stream);

	tga->buffer = decode_tga(tga);
	
	fill_tga_image(tga);

	fclose(stream);
	
	return (0);
}
