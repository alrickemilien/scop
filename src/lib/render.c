static void	auto_rotate_object(void)
{
	matrix_rotate_y(g_scop.model_matrix, 0.001f);
}

static void	update_texture_transition(void)
{
	if (g_scop.texturing)
	{
		if (g_scop.texture_level < 1.0f)
			g_scop.texture_level += 0.01f;
		else if (g_scop.texture_level > 1.0f)
			g_scop.texture_level = 1.0f;
	}
	else if (!g_scop.texturing)
	{
		if (g_scop.texture_level > 0.0f)
			g_scop.texture_level -= 0.01f;
		else if (g_scop.texture_level < 0.0f)
			g_scop.texture_level = 0.0f;
	}
}

void		render(t_software_environ *env)
{
	static float	mvp[16] = { 0 };

	if (env->auto_rotate)
		auto_rotate_object();

	update_texture_transition();

	matrix_identity(mvp);

	matrix_mult_m(mvp, 3, env->model_matrix, env->view_matrix, env->proj_matrix);

	glUniformMatrix4fv(env->model_matrix_uni, 1, GL_FALSE, env->model_matrix);

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp);

	glUniform1f(env->texture_level_uni, env->texture_level);

	glDrawArrays(GL_TRIANGLES, 0, env->vertex_count);
}
