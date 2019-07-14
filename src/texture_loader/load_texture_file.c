#include "scop.h"

int load_texture_file(
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
    {
        texture->data = texture->bmp.buffer;
        texture->width = texture->bmp.dib_header.bits_per_pixel;
        texture->height = texture->bmp.width;
        texture->pixel_depth = texture->bmp.height;
        texture->format = GL_BGR;
	    if (texture->bmp.dib_header.bits_per_pixel == 32)
		    texture->format = GL_BGRA;
		return (0);
    }
	if (load_tga_file(&texture->tga, pathname) != -1)
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

    texture->is_texture_loaded = false;

    return (0);
}