#include "scop.h"

/*
** Load a txture int OpenGL soft
*/

void	load_texture(t_software_environ *env)
{
	glGenTextures(1, env->bmp.buffer);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, env->bmp.buffer);

	glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGB,
					env->bmp.width,
					env->bmp.height,
					0,
					GL_BGR,
					GL_UNSIGNED_BYTE,
					env->bmp.buffer);

	glUniform1i(glGetUniformLocation(env->object_shader_program.id, "texture"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
