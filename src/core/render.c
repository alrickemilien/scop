#include "scop.h"

/*
static void	update_texture_transition(t_software_environ *env)
{
	if (env->texturing)
	{
		if (env->texture_level < 1.0f)
			env->texture_level += 0.01f;
		else if (env->texture_level > 1.0f)
			env->texture_level = 1.0f;
	}

	else if (!env->texturing)
	{
		if (env->texture_level > 0.0f)
			env->texture_level -= 0.01f;
		else if (env->texture_level < 0.0f)
			env->texture_level = 0.0f;
	}
}
*/

void		render(t_software_environ *env)
{
	t_matrix *mvp;
	size_t i;

	i = 0;

	//	if (env->auto_rotate)
	//		rotate_x_matrix4x4(env->model_matrix, 1.0f);

	//	update_texture_transition(env);

 	mvp = identity_matrix(4, 4);

	i = 0;
	while (i < env->model_matrix->lines * env->model_matrix->columns)
	{
		if (i && (i + 1) % 4 == 0) {
			printf("%lf \n",env->model_matrix->value[i]);
		} else {
			printf("%lf ",env->model_matrix->value[i]);
		}

		i++;
	}

	multiply_matrix(mvp, env->model_matrix, mvp);

	multiply_matrix(mvp, env->view_matrix, mvp);

	multiply_matrix(mvp, env->projection_matrix, mvp);

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

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, c);

//	glUniformMatrix4fv(env->model_matrix_uni, 1, GL_FALSE, b);

//	glUniform1f(env->texture_level_uni, env->texture_level);

	glUseProgram(env->program_id);
	glBindVertexArray(env->vao);
	glDrawArrays(GL_TRIANGLES, 0, 10);

	delete_matrix(mvp);
}
