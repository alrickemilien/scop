#include "scop.h"

static void extract_tga_infos_from_header(
	t_tga *tga,
	t_tga_header *header)
{
	tga->width = (size_t)*(uint16_t*)&header->image_spec[0x6];
	tga->height = (size_t)*(uint16_t*)&header->image_spec[0x4];
	tga->pixel_depth = (size_t)header->image_spec[0x8];
}

static int				fill_tga_header(
	t_tga *tga,
	t_tga_header *header,
	FILE *stream)
{
	uint8_t				buff[18];
	size_t				i;
	size_t				size_read;

	if ((size_read = fread(buff, 1, 18, stream)) != 18)
	{
		fprintf(stderr, "%ld has been read\n", size_read);
		
		return (-1);
	}

	header->id_length = buff[0];
	header->color_map_type = buff[1];
	header->image_type = buff[2];

	i = 3;
	while (i < 18)
	{
		if (i < 8)
			header->color_map_spec[i - 3] = buff[i];
		else
			header->image_spec[i - 8] = buff[i];
		i++;
	}

	extract_tga_infos_from_header(tga, header);

	
	printf("header->id_length: %ld\n"
		"header->color_map_type: %ld\n"
		"header->image_type: %ld\n"
		"header->width: %ld\n"
		"header->height: %ld\n"
		"header->pixel_depth: %ld\n",
		(size_t)header->id_length,
		(size_t)header->color_map_type,
		(size_t)header->image_type,
		(size_t)tga->width,
		(size_t)tga->height,
		(size_t)tga->pixel_depth);

	return (0);
}

static int	load_tga_image(t_tga *tga, FILE *stream)
{
	size_t			size;
	size_t			size_read;

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
			y++;
			z = (tga->height - (y + 1)) * tga->width * 4;
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

	if (fill_tga_header(tga, &tga->header, stream))
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

	tga->image = (uint32_t*)malloc(sizeof(uint32_t) * tga->width * tga->height);

	load_tga_image(tga, stream);

	tga->buffer = decode_tga(tga);
	
	fill_tga_image(tga);

	free(tga->buffer);

	fclose(stream);
	
	return (0);
}
