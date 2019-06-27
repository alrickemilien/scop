#ifndef BMP_H
# define BMP_H

#pragma pack(push, 1)
typedef struct			s_bmp_header
{
	char				type[2];
	unsigned			size;
	short				reserved1;
	short				reserved2;
	unsigned			data_offset;
}						t_bmp_header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct			s_bmp_dib_header
{
	unsigned			header_size;
	int					image_width;
	int					image_height;
	short				color_planes;
	short				bits_per_pixel;
	unsigned			compression_method;
	unsigned			image_size;
	int					horizontal_resolution;
	int					vertical_resolution;
	int					colors;
	int					important_colors;
}						t_bmp_dib_header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct			s_bitmap {
	char				*path;
	t_bmp_header		header;
	t_bmp_dib_header	dib_header;
	char				*buffer;
	size_t				width;
	size_t				height;
}						t_bitmap;
#pragma pack(pop)

int						load_bitmap_file(
							t_bitmap *bmp,
							char const *pathname);

#endif
