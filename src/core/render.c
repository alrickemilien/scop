#include "scop.h"

void		render(t_software_environ *env)
{
	t_mat4 *mvp;
	size_t i;

	i = 0;

	// if (env->auto_rotate)
			// rotate_y_mat4(env->model_matrix, 1.0f);

 	mvp = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	GLfloat b[16];

	i = 0;
	while (i < 16)
	{
		b[i] = (GLfloat)env->model_matrix->value[i];
		i++;
	}

	GLfloat c[16];

	i = 0;
	while (i < 16)
	{
		c[i] = (GLfloat)mvp->value[i];
		i++;
	}

	i = 0;
	while (i < 16)
	{
		if (i && (i + 1) % 4 == 0) {
			printf("%lf \n",c[(i % 4) * 4 + (i % 4)]);
		} else {
			printf("%lf ",c[(i % 4) * 4 + (i % 4)]);
		}

		i++;
	}

	printf("\n");

	// GL_TRUE indicates that is is row major matrix
	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, c);

	// glUniformMatrix4fv(env->model_matrix_uni, 1, GL_FALSE, b);

	// glUniform1f(env->texture_level_uni, env->texture_level);

	glUseProgram(env->program_id);

	glBindVertexArray(env->vao);
	glDrawArrays(GL_TRIANGLES, 0, env->data.vertex_count);

	glBindVertexArray(env->plan_vao);
	glDrawArrays(GL_TRIANGLES, 0, 50 * 50 * 4);

	delete_matrix(mvp);
}
