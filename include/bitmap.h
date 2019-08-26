/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 21:01:26 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 21:01:27 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# pragma pack(push, 1)

typedef struct			s_bmp_header
{
	uint8_t				type[2];
	uint32_t			size;
	uint16_t			reserved1;
	uint16_t			reserved2;
	uint32_t			data_offset;
}						t_bmp_header;

# pragma pack(pop)

# pragma pack(push, 1)

typedef struct			s_bmp_dib_header
{
	uint32_t			header_size;
	uint32_t			image_width;
	uint32_t			image_height;
	uint16_t			color_planes;
	uint16_t			bits_per_pixel;
	uint32_t			compression_method;
	uint32_t			image_size;
	uint32_t			horizontal_resolution;
	uint32_t			vertical_resolution;
	uint32_t			colors;
	uint32_t			important_colors;
}						t_bmp_dib_header;

# pragma pack(pop)

typedef struct			s_bitmap {
	char				*path;
	t_bmp_header		header;
	t_bmp_dib_header	dib_header;
	uint8_t				*buffer;
	size_t				width;
	size_t				height;
	size_t				size;
}						t_bitmap;

int						load_bitmap_file_header(
		t_bitmap *bmp,
		FILE *stream);

int						load_bitmap_file(
		t_bitmap *bmp,
		char const *pathname);
#endif
