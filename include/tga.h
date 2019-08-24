#ifndef TGA_H
# define TGA_H

/*
** Load TGA files
*/

# define NON_COMPRESSED_TGA 2

#pragma pack(push, 1)
typedef struct			s_tga_header
{
	uint8_t				id_length;
	uint8_t				color_map_type;
	uint8_t				image_type;
	uint8_t				color_map_spec[5];
	uint8_t				image_spec[10];
}						t_tga_header;
#pragma pack(pop)

typedef struct			s_tga
{
	char				*path;
	t_tga_header		header;
	uint8_t				*buffer;
	uint32_t			*image;
	size_t				width;
	size_t				height;
	size_t				pixel_depth;
}						t_tga;

int						fill_tga_header(
							t_tga *tga,
							t_tga_header *header,
							FILE *stream);
uint32_t				uint32_color(
    						uint8_t alpha,
    						uint8_t red,
    						uint8_t green,
    						uint8_t blue);
uint8_t					*decode_tga(
							t_tga *tga);
int						load_tga_file(
							t_tga *tga,
							const char *pathname);

#endif
