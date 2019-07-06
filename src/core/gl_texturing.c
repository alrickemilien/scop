#include "scop.h"

/*
** Load a txture int OpenGL soft
*/

int	gl_texturing(t_software_environ *env)
{
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

	glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGB,
					env->bmp.width,
					env->bmp.height,
					0,
					GL_BGR,
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


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return (0);
}
