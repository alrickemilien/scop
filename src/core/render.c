#include "scop.h"

static void render_vao(GLuint vao, GLenum render_style, size_t vertex_number) {
	glBindVertexArray(vao);
	glDrawArrays(render_style, 0, vertex_number);
	glBindVertexArray(0);
}

void		render(t_software_environ *env)
{
	t_mat4 *mvp;
	// t_vec3 b;
	size_t i;

	i = 0;

	if (env->auto_rotate)
		rotate_y_mat4(env->model_matrix, 0.1f);

 	mvp = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	// GL_TRUE indicates that is is row major matrix
	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp->value);

	// b = compute_object_barycentre(env->data.positions);
	// glUniform3f(env->barycentre_uni, b.x, b.y, b.z);

	// glUniform1f(env->texture_level_uni, env->texture_level);

	glUseProgram(env->object_shader_program.id);
	render_vao(env->vao, GL_TRIANGLES, env->data.vertex_count);

	glUseProgram(env->internal_object_shader_program.id);
	render_vao(env->plan_vao, GL_POINTS, 1);

	// glUseProgram(env->axis_shader_program.id);
	// render_vao(env->axis_vao, GL_POINTS, 1);

	
	
	delete_matrix(mvp);
}
