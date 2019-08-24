#include "scop.h"

static void				extract_tga_infos_from_header(
	t_tga *tga,
	t_tga_header *header)
{
	tga->width = (size_t)*(uint16_t*)&header->image_spec[0x6];
	tga->height = (size_t)*(uint16_t*)&header->image_spec[0x4];
	tga->pixel_depth = (size_t)header->image_spec[0x8];
}

static void				tga_debug(
	const t_tga *tga,
	const t_tga_header *header)
{
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
}

int						fill_tga_header(
	t_tga *tga,
	t_tga_header *header,
	FILE *stream)
{
	uint8_t	buff[18];
	size_t	i;
	size_t	size_read;

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
	(void)tga_debug;
	return (0);
}
