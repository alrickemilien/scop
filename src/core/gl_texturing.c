#include "scop.h"

/*
** Load a texture into OpenGL soft
*/

int	gl_texturing(t_software_environ *env)
{
    env->grey_scale_uni = glGetUniformLocation(env->object_shader_program.id, "grey_scale");

	if (!env->texture.is_texture_loaded)
		return (0);

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
					env->texture.width,
					env->texture.height,
					0,
					env->texture.format,
					GL_UNSIGNED_BYTE,
					env->texture.data);

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
