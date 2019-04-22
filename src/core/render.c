#include "scop.h"

void		render(t_software_environ *env)
{
	t_mat4 *mvp;
	size_t i;

	i = 0;

	//	if (env->auto_rotate)
	//		rotate_x_matrix4x4(env->model_matrix, 1.0f);

 	mvp = identity_mat4();

	multiply_matrix(mvp, env->projection_matrix, mvp);

	multiply_matrix(mvp, env->view_matrix, mvp);

	multiply_matrix(mvp, env->model_matrix, mvp);

	// i = 0;
	// while (i < mvp->lines * mvp->columns)
	// {
	// 	if (i && (i + 1) % 4 == 0) {
	// 		printf("%lf \n",mvp->value[i]);
	// 	} else {
	// 		printf("%lf ",mvp->value[i]);
	// 	}

	// 	i++;
	// }

	// printf("\n");

	GLfloat b[16];

	i = 0;
	while (i < env->model_matrix->lines * env->model_matrix->columns)
	{
		b[i] = (GLfloat)env->model_matrix->value[i];
		i++;
	}

	GLfloat c[16];

	i = 0;
	while (i < mvp->lines * mvp->columns)
	{
		c[i] = (GLfloat)mvp->value[i];
		i++;
	}

	i = 0;
	while (i < mvp->lines * mvp->columns)
	{
		if (i && (i + 1) % 4 == 0) {
			printf("%lf \n",c[i]);
		} else {
			printf("%lf ",c[i]);
		}

		i++;
	}

	printf("\n");

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, c);

	// glUniformMatrix4fv(env->model_matrix_uni, 1, GL_FALSE, b);

	// glUniform1f(env->texture_level_uni, env->texture_level);

	glUseProgram(env->program_id);
	glBindVertexArray(env->vao);
	glDrawArrays(GL_TRIANGLES, 0, env->data.vertex_count);

	delete_matrix(mvp);
}
