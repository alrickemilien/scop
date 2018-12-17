#include "scop.h"

void prepare(t_software_environ *env)
{
	glGenVertexArrays(1, &env->vertex_array);
	glBindVertexArray(env->vertex_array);

	// Load the attributes
	set_attribute(env->program_id, "position");
	set_attribute(env->program_id, "color");
	set_attribute(env->program_id, "uv");
	set_attribute(env->program_id, "normal");

	load_texture(env);

	env->view_matrix = new_matrix();
	env->.model_matrix = scale_matrix4x4(0.2f);
	env->.proj_matrix = perspective_fmatrix4x4(
		deg_to_rad(60.0f),
		800.0f / 600.0f,
		0.0f,
		1000.0f);

	env->mvp_uni = glGetUniformLocation(env->program, "mvp");
	env->model_matrix_uni = glGetUniformLocation(env->program, "modelMatrix");
	env->lighting_uni = glGetUniformLocation(env->program, "lighting");

	glUniform1i(env->lighting_uni, env->lighting);

	env->texture_level_uni = glGetUniformLocation(env->program, "textureLevel");

	glUniform1f(env->texture_level_uni, env->texture_level);

	set_light_uniforms();
}
