#include "scop.h"

static void	set_light_uniforms(t_software_environ *env)
{
	env->light_position_uni = glGetUniformLocation(env->program_id,
		"lightPosition");

	glUniform3f(
		env->light_position_uni,
		env->light.position.x,
		env->light.position.y,
		env->light.position.z);

	env->light_color_uni = glGetUniformLocation(env->program_id,
		"lightColor");

	glUniform3f(
		env->light_color_uni,
		env->light.color.x,
		env->light.color.y,
		env->light.color.z);
}

void prepare(t_software_environ *env)
{
	glGenVertexArrays(1, &env->vertex_array);
	glBindVertexArray(env->vertex_array);

	// Load the vriables taht will be use into shaders
	// the variables id will be stored in env structure
	// with the fields of the same name
	set_attribute(env->program_id, "position");
	set_attribute(env->program_id, "color");
	set_attribute(env->program_id, "uv");
	set_attribute(env->program_id, "normal");

	load_texture(env);

	env->view_matrix = new_matrix(4, 4);
	env->model_matrix = scale_matrix4x4(0.2);
	env->projection_matrix = perspective_matrix4x4(
		deg_to_rad(60.0f),
		800.0f / 600.0f,
		0.0f,
		1000.0f);

	env->mvp_uni = glGetUniformLocation(env->program_id, "mvp");
	env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");
	env->lighting_uni = glGetUniformLocation(env->program_id, "lighting");

	glUniform1i(env->lighting_uni, env->lighting);

	env->texture_level_uni = glGetUniformLocation(env->program_id, "textureLevel");

	glUniform1f(env->texture_level_uni, env->texture_level);

	set_light_uniforms(env);
}
