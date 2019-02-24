#include "scop.h"

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

void		render(t_software_environ *env)
{
	t_matrix *mvp;

	if (env->auto_rotate)

	rotate_x_matrix4x4(env->model_matrix, 1.0f);

	update_texture_transition(env);

 	mvp = identity_matrix(4, 4);

	multiply_matrix(mvp, env->model_matrix, mvp);

	multiply_matrix(mvp, env->view_matrix, mvp);

	multiply_matrix(mvp, env->projection_matrix, mvp);

	pmatrix("%lf", mvp);

	glUniformMatrix4fv(env->model_matrix_uni, 1, GL_FALSE, (GLfloat*) env->model_matrix->value);

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, (GLfloat*) mvp->value);

	glUniform1f(env->texture_level_uni, env->texture_level);

	glDrawArrays(GL_TRIANGLES, 0, env->data.vertex_count);
}
