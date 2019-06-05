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
	t_vec3 camera_position;
    t_vec3 camera_look_at_position;
    t_vec3 camera_up;

	// camera_position = (t_vec3){ 5.f, 5.f, 5.f };
    // camera_look_at_position = (t_vec3){ 0.f, 0.f, 0.f };
    // camera_up = (t_vec3){ 0.f, 1.f, 0.f };

	smart_camera_position(env,
		&camera_position,
		&camera_look_at_position,
		&camera_up);

	env->view_matrix = look_at_mat4(
		&camera_position,
		&camera_look_at_position,
		&camera_up
	);

	env->projection_matrix = perspective_mat4(
		90.0f,
		(GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT),
		1.0f,
		2000.0f);

	env->mvp_uni = glGetUniformLocation(env->object_shader_program.id, "mvp");

	env->internal_object_mvp_uni = glGetUniformLocation(env->internal_object_shader_program.id, "mvp");
}