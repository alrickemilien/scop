/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:29:41 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:29:42 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	load_tga_texture_file(t_texture *texture)
{
	texture->data = texture->tga.image;
	texture->width = texture->tga.width;
	texture->height = texture->tga.height;
	texture->pixel_depth = texture->tga.pixel_depth;
	texture->format = GL_RGB;
	if (texture->pixel_depth == 32)
		texture->format = GL_RGBA;
	return (0);
}

static int	load_bitmap_texture_file(t_texture *texture)
{
	texture->data = texture->bmp.buffer;
	texture->width = texture->bmp.width;
	texture->height = texture->bmp.height;
	texture->pixel_depth = texture->bmp.dib_header.bits_per_pixel;
	texture->format = GL_BGR;
	if (texture->bmp.dib_header.bits_per_pixel == 32)
		texture->format = GL_BGRA;
	return (0);
}

int			load_texture_file(
		t_texture *texture,
		const char *pathname)
{
	if (pathname == NULL)
	{
		texture->is_texture_loaded = false;
		return (0);
	}
	texture->is_texture_loaded = true;
	if (load_bitmap_file(&texture->bmp, pathname) != -1)
		return (load_bitmap_texture_file(texture));
	if (load_tga_file(&texture->tga, pathname) != -1)
		return (load_tga_texture_file(texture));
	texture->is_texture_loaded = false;
	return (0);
}
