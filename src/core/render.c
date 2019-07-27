#include "scop.h"

static void		render_vao(GLuint vao, GLenum render_style, size_t vertex_number)
{
	glBindVertexArray(vao);
	glDrawArrays(render_style, 0, vertex_number);
}

static void		render_elements(GLuint vao, GLenum render_style, size_t vertex_number) 
{
 		glBindVertexArray(vao);

		 // Draw the triangles !
 		glDrawElements(
     		render_style,
     		vertex_number,
     		GL_UNSIGNED_INT,
     		(void*)0
 		);
}

static t_matrix	*rotate_object_around_point(t_software_environ *env, t_vec3 v)
{
	t_matrix *model_matrix;
	t_vec3 minus_v;

	minus_v = (t_vec3){-v.x, -v.y, -v.z};

	model_matrix = identity_mat4();

	env->translation_matrix = identity_mat4();
	translate_mat4(env->translation_matrix, &v);
	multiply_mat4(model_matrix, env->translation_matrix, model_matrix);

	env->rotation_matrix = identity_mat4();
	rotate_y_mat4(env->rotation_matrix, env->y_auto_rotate_angle);
	multiply_mat4(model_matrix, env->rotation_matrix, model_matrix);

	delete_matrix(env->translation_matrix);
	env->translation_matrix = identity_mat4();
	translate_mat4(env->translation_matrix, &minus_v);
	multiply_mat4(model_matrix, env->translation_matrix, model_matrix);

	return model_matrix;
}

static void		apply_rotation(t_software_environ *env) {
	t_vec3	minus_b;
	t_vec3	b;

	b = compute_object_barycentre(env->data.positions);

	b.x += env->mesh_offset.x;
	b.y += env->mesh_offset.y;
	b.z += env->mesh_offset.z;

	minus_b = (t_vec3){-b.x, -b.y, -b.z};

	// printf("BARYCENTRE : .x %f .y %f .z %f \n", b.x, b.y, b.z);
	
	env->y_auto_rotate_angle += 0.5f;
	if (env->y_auto_rotate_angle >= 360.f)
		env->y_auto_rotate_angle = 30.f;

	env->model_matrix = rotate_object_around_point(env, minus_b);

	// printmat4(env->model_matrix->value);
}

void			render_mesh(t_software_environ *env, t_matrix *mvp)
{
	// printf("ici\n");
	// check_gl_error();

	glUseProgram(env->object_shader_program.id);
	// printf("la\n");
	// check_gl_error();

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp->value);
	// printf("1\n");
	// check_gl_error();


	glUniformMatrix4fv(env->m_uni, 1, GL_FALSE, env->model_matrix->value);
	// printf("2\n");
	// check_gl_error();

	glUniformMatrix4fv(env->v_uni, 1, GL_FALSE, env->view_matrix->value);
	// printf("3\n");
	// check_gl_error();


	glUniformMatrix4fv(env->p_uni, 1, GL_FALSE, env->projection_matrix->value);
	// printf("3bis\n");
	// check_gl_error();

	glUniform1f(env->ambient_lighting_uni, env->ambient_lighting);
	// printf("4\n");
	// check_gl_error();


	glUniform1f(env->specular_lighting_uni, env->specular_lighting);
	// printf("5\n");
	// check_gl_error();


	glUniform3fv(env->light_uni, 1, (GLfloat*)(&env->light_position));
	// printf("6\n");
	// check_gl_error();

    glUniform3fv(env->eye_uni, 1, (GLfloat*)(&env->camera_position));
	// printf("7\n");

	// check_gl_error();

    glUniform3fv(env->mesh_offset_uni, 1, (GLfloat*)(&env->mesh_offset));
	// printf("7\n");

	// check_gl_error();

	// printf("8\n");

	glUniform1i(env->texture_uni, 0);
	//  check_gl_error();

	// printf("9\n");
	//  check_gl_error();

    glUniform1i(env->grey_scale_uni, env->grey_scale);

    glUniform1i(env->is_texture_uni, env->is_texture_rendered);

	if (env->indexation_mode)
		render_elements(env->vao, env->render_style, env->data.vertex_count);
	else
		render_vao(env->vao, env->render_style, env->data.vertex_count);

}

void			render_meshs_normals(t_software_environ *env, t_matrix *mvp)
{
	if (env->render_style == GL_TRIANGLES && env->render_normals)
	{
		glUseProgram(env->normals_shader_program.id);

		glUniformMatrix4fv(env->normal_mvp_uni, 1, GL_FALSE, mvp->value);
		glUniformMatrix4fv(env->normal_m_uni, 1, GL_FALSE, env->model_matrix->value);
		glUniformMatrix4fv(env->normal_v_uni, 1, GL_FALSE, env->view_matrix->value);
		glUniformMatrix4fv(env->normal_p_uni, 1, GL_FALSE, env->projection_matrix->value);

		if (env->indexation_mode)
			render_elements(env->vao, env->render_style, env->data.vertex_count);
		else
			render_vao(env->vao, env->render_style, env->data.vertex_count);
	}
}

void			render_plan(t_software_environ *env)
{
	t_matrix *mvp;
	
	env->model_matrix = identity_mat4();

	mvp = compute_mvp(env);

	glUseProgram(env->internal_object_shader_program.id);

	// GL_TRUE indicates that is is row major matrix
	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);

	render_vao(env->plan_vao, GL_POINTS, 1);

	delete_matrix(mvp);
	delete_matrix(env->model_matrix);
}

void			render_axis(t_software_environ *env)
{
	t_matrix *mvp;

	env->model_matrix = identity_mat4();

	mvp = compute_mvp(env);

	glUseProgram(env->axis_shader_program.id);

	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);

	render_vao(env->axis_vao, GL_POINTS, 1);

	delete_matrix(mvp);
	delete_matrix(env->model_matrix);
}

void			render(t_software_environ *env)
{
	t_mat4 *mvp;

	apply_rotation(env);

	mvp = compute_mvp(env);

	//
	// MESH
	//

	render_mesh(env, mvp);

	//
	// MESH NORMALS
	//

	render_meshs_normals(env, mvp);

	delete_matrix(mvp);
	delete_matrix(env->model_matrix);
	delete_matrix(env->translation_matrix);
	delete_matrix(env->rotation_matrix);

	//
	// PLAN
	//

	render_plan(env);

	//
	// AXIS
	//

	render_axis(env);
}
