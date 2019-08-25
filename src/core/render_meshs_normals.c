#include "scop.h"

void			render_meshs_normals(t_software_environ *env, t_matrix *mvp)
{
	if (env->render_style == GL_TRIANGLES && env->render_normals)
	{
		glUseProgram(env->normals_shader_program.id);
		glUniformMatrix4fv(
				env->normal_mvp_uni, 1, GL_FALSE, mvp->value);
		glUniformMatrix4fv(
				env->normal_m_uni, 1, GL_FALSE, env->model_matrix.value);
		glUniformMatrix4fv(
				env->normal_v_uni, 1, GL_FALSE, env->view_matrix.value);
		glUniformMatrix4fv(
				env->normal_p_uni, 1, GL_FALSE, env->projection_matrix.value);
		if (env->indexation_mode)
			render_elements(
					env->vao, env->render_style, env->data.vertex_count);
		else
			render_vao(env->vao, env->render_style, env->data.vertex_count);
	}
}
