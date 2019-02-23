#include "scop.h"

/*
** Load a txture int OpenGL soft
*/

void	load_texture(t_software_environ *env)
{
	size_t						width;
	size_t						height;
	unsigned char	*image_buffer;

	glGenTextures(1, &env->texture);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, env->texture);

	image_buffer = load_bitmap_file(env->path_to_texture, &width, &height);

	glTexImage2D(GL_TEXTURE_2D,
								0,
								GL_RGB,
								width,
								height,
								0,
								GL_BGR,
								GL_UNSIGNED_BYTE,
								image_buffer);

	free(image_buffer);

	glUniform1i(glGetUniformLocation(env->program_id, "texture"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
