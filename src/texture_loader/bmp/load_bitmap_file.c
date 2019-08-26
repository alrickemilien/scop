/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bitmap_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:31:18 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:31:19 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	load_bitmap_file_error(
	const char *pathname,
	FILE *stream)
{
	fprintf(stderr, "Unable to load file %s\n", pathname);
	if (stream)
		fclose(stream);
	return (-1);
}

int			load_bitmap_file(
	t_bitmap *bmp,
	const char *pathname)
{
	FILE	*stream;
	size_t	size_read;

	printf("Start loading bitmap file %s\n", pathname);
	memset(bmp, 0, sizeof(t_bitmap));
	if ((stream = fopen(pathname, "rb")) == NULL)
		return (load_bitmap_file_error(pathname, stream));
	if (load_bitmap_file_header(bmp, stream) < 0)
		return (load_bitmap_file_error(pathname, stream));
	fseek(stream, bmp->header.data_offset, SEEK_SET);
	bmp->buffer = (uint8_t*)malloc(bmp->size * sizeof(uint8_t));
	size_read = fread(bmp->buffer, 1, bmp->size, stream);
	if (bmp->dib_header.image_size != 0
		&& size_read != bmp->size)
	{
		free(bmp->buffer);
		bmp->buffer = NULL;
		fclose(stream);
		return (-1);
	}
	return (fclose(stream));
}
