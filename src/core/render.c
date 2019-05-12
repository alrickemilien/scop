#include "scop.h"

static void render_vao(GLuint vao, GLenum render_style, size_t vertex_number) {
	glBindVertexArray(vao);
	glDrawArrays(render_style, 0, vertex_number);
	glBindVertexArray(0);
}

void		render(t_software_environ *env)
{
	t_mat4 *mvp;
	size_t i;

	i = 0;

	if (env->auto_rotate)
		rotate_y_mat4(env->model_matrix, 0.1f);

 	mvp = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	// GL_TRUE indicates that is is row major matrix
	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp);

	// glUniform1f(env->texture_level_uni, env->texture_level);

	glUseProgram(env->program_id);

	render_vao(env->vao, GL_TRIANGLES, env->data.vertex_count);
	render_vao(env->plan_vao, GL_LINES, 50 * 50 * 4);

	delete_matrix(mvp);
}
