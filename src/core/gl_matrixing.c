#include "scop.h"

/*
** Compute rotation matrix according to object barycentre
*/

/*
** Setup matrix uniforms
*/

static void	gl_matrixing_uniforms(t_software_environ *env)
{
	env->mvp_uni = glGetUniformLocation(
			env->object_shader_program.id, "mvp");
	env->m_uni = glGetUniformLocation(
			env->object_shader_program.id, "m");
	env->v_uni = glGetUniformLocation(
			env->object_shader_program.id, "v");
	env->p_uni = glGetUniformLocation(
			env->object_shader_program.id, "p");
	env->mesh_offset_uni = glGetUniformLocation(
			env->object_shader_program.id, "mesh_offset");
	env->eye_uni = glGetUniformLocation(
			env->object_shader_program.id, "eye");
	env->internal_object_mvp_uni = glGetUniformLocation(
			env->internal_object_shader_program.id, "mvp");
	env->normal_mvp_uni = glGetUniformLocation(
			env->normals_shader_program.id, "mvp");
	env->normal_m_uni = glGetUniformLocation(
			env->normals_shader_program.id, "m");
	env->normal_v_uni = glGetUniformLocation(
			env->normals_shader_program.id, "v");
	env->normal_p_uni = glGetUniformLocation(
			env->normals_shader_program.id, "p");
}

/*
** Setup matrix's for object transformation
** into gl context
*/

void		gl_matrixing(t_software_environ *env)
{
	t_vec3	camera_position;
	t_vec3	camera_look_at_position;
	t_vec3	camera_up;

	smart_camera_position(env,
		&camera_position,
		&camera_look_at_position,
		&camera_up);
	env->camera_position = camera_position;
	env->view_matrix = look_at_mat4(
		&camera_position,
		&camera_look_at_position,
		&camera_up);
	env->projection_matrix = perspective_mat4(
		90.0f,
		(GLfloat)(env->window_width / env->window_height),
		1.0f,
		2000.0f);
	check_gl_error();
	gl_matrixing_uniforms(env);
}
