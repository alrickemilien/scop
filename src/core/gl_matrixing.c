#include "scop.h"

/*
** Setup matrix's for object transformation
** into gl context
*/

void gl_matrixing(t_software_environ *env)
{
	env->view_matrix = identity_mat4();

	env->model_matrix = scale_mat4(0.1);

	env->projection_matrix = perspective_mat4(
		deg_to_rad(60.0),
		800.0 / 600.0,
		0.0,
		1000.0);

	env->mvp_uni = glGetUniformLocation(env->program_id, "mvp");

	// env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");
}