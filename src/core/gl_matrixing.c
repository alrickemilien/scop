#include "scop.h"

/*
** Setup matrix's for object transformation
** into gl context
*/

void gl_matrixing(t_software_environ *env)
{
	t_vec3 camera_position = { 4.f, 4.f, 4.f };
    t_vec3 camera_look_at_position = { 0.f, 0.f, 0.f };
    t_vec3 camera_up = { 0.f, 0.f, 1.f };

	env->view_matrix = look_at_mat4_2(
		&camera_position,
		&camera_look_at_position,
		&camera_up
	);

	env->model_matrix = identity_mat4();

	env->projection_matrix = perspective_mat4(
		deg_to_rad(60.0f),
		800.0f / 600.0f,
		0.0f,
		1000.0f);

	env->mvp_uni = glGetUniformLocation(env->program_id, "mvp");

	// env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");
}