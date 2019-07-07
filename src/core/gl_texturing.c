#include "scop.h"

/*
** Load a texture into OpenGL soft
*/

int	gl_texturing(t_software_environ *env)
{
	GLenum format;

	printf("0\n");
	check_gl_error();
	
	glGenTextures(1, &env->texture_id);

	printf("1\n");
	check_gl_error();

	glActiveTexture(GL_TEXTURE0);

	printf("2\n");
	check_gl_error();

	glBindTexture(GL_TEXTURE_2D, env->texture_id);
	printf("3\n");
	check_gl_error();

	printf("env->bmp.width : %d\n", env->bmp.width);
	printf("env->bmp.height : %d\n", env->bmp.height);

	format = GL_BGR;
	if (env->bmp.dib_header.bits_per_pixel == 32)
		format = GL_BGRA;

	glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGB,
					env->bmp.width,
					env->bmp.height,
					0,
					format,
					GL_UNSIGNED_BYTE,
					env->bmp.buffer);
	printf("4\n");
	check_gl_error();

	env->texture_uni = glGetUniformLocation(env->object_shader_program.id, "texture_sample");
	printf("5\n");
	check_gl_error();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	printf("8\n");
	check_gl_error();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	printf("7\n");
	check_gl_error();

	return (0);
}
