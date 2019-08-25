#include "scop.h"

void			render_mesh(t_software_environ *env, t_matrix *mvp)
{
	glUseProgram(env->object_shader_program.id);
	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp->value);
	glUniformMatrix4fv(env->m_uni, 1, GL_FALSE, env->model_matrix.value);
	glUniformMatrix4fv(env->v_uni, 1, GL_FALSE, env->view_matrix.value);
	glUniformMatrix4fv(env->p_uni, 1, GL_FALSE, env->projection_matrix.value);
	glUniform1f(env->ambient_lighting_uni, env->ambient_lighting);
	glUniform1f(env->specular_lighting_uni, env->specular_lighting);
	glUniform3fv(env->light_uni, 1, (GLfloat*)(&env->light_position));
	glUniform3fv(env->eye_uni, 1, (GLfloat*)(&env->camera_position));
	glUniform3fv(env->mesh_offset_uni, 1, (GLfloat*)(&env->mesh_offset));
	glUniform1i(env->texture_uni, 0);
	check_gl_error();
	glUniform1i(env->grey_scale_uni, env->grey_scale);
	glUniform1i(env->is_texture_uni, env->is_texture_rendered);
	if (env->indexation_mode)
		render_elements(env->vao, env->render_style, env->data.vertex_count);
	else
		render_vao(env->vao, env->render_style, env->data.vertex_count);
}
