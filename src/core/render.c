#include "scop.h"

void			render_vao(
		GLuint vao,
		GLenum render_style,
		size_t vertex_number)
{
	glBindVertexArray(vao);
	glDrawArrays(render_style, 0, vertex_number);
}

void			render_elements(
		GLuint vao,
		GLenum render_style,
		size_t vertex_number)
{
	glBindVertexArray(vao);
	glDrawElements(
			render_style,
			vertex_number,
			GL_UNSIGNED_INT,
			(void*)0);
}

void			render_plan(t_software_environ *env, t_mat4 *mvp)
{
	identity_mat4(&env->model_matrix);
	compute_mvp(env, mvp);
	glUseProgram(env->internal_object_shader_program.id);
	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);
	render_vao(env->plan_vao, GL_POINTS, 1);
}

void			render_axis(t_software_environ *env, t_mat4 *mvp)
{
	identity_mat4(&env->model_matrix);
	compute_mvp(env, mvp);
	glUseProgram(env->axis_shader_program.id);
	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);
	render_vao(env->axis_vao, GL_POINTS, 1);
}

void			render(t_software_environ *env)
{
	t_mat4 mvp;

	apply_rotation(env);
	compute_mvp(env, &mvp);
	render_mesh(env, &mvp);
	render_meshs_normals(env, &mvp);
	render_plan(env, &mvp);
	render_axis(env, &mvp);
}
