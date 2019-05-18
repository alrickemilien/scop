#include "scop.h"

/*
** Compute rotation matrix according to object barycentre
*/

/*
** Setup matrix's for object transformation
** into gl context
*/

void gl_matrixing(t_software_environ *env)
{
	t_vec3 camera_position = { 4.f, 6.f, 4.f };
    t_vec3 camera_look_at_position = { 0.f, 0.f, 0.f };
    t_vec3 camera_up = { 0.f, 1.f, 0.f };

	env->view_matrix = look_at_mat4(
		&camera_position,
		&camera_look_at_position,
		&camera_up
	);

	env->model_matrix = identity_mat4();

	env->projection_matrix = perspective_mat4(
		90.0f,
		(GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT),
		1.0f,
		2000.0f);

	env->mvp_uni = glGetUniformLocation(env->object_shader_program.id, "mvp");
	env->barycentre_uni = glGetUniformLocation(env->object_shader_program.id, "barycentre");

	env->mvp_uni = glGetUniformLocation(env->internal_object_shader_program.id, "mvp");

	// env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");
}