#include "scop.h"

static void render_vao(GLuint vao, GLenum render_style, size_t vertex_number) {
	glBindVertexArray(vao);
	glDrawArrays(render_style, 0, vertex_number);
}

void		render(t_software_environ *env)
{
	t_mat4 *mvp;
	t_vec3 b;
	t_vec3 minus_b;

	b = compute_object_barycentre(env->data.positions); 
	// glUniform3f(env->barycentre_uni, b.x, b.y, b.z);
	// printf("BARYCENTRE : .x %f .y %f .z %f \n", b.x, b.y, b.z);

	minus_b = (t_vec3){-b.x, -b.y, -b.z};
	
	env->y_auto_rotate_angle += 0.5f;
	if (env->y_auto_rotate_angle >= 360.f)
		env->y_auto_rotate_angle = 0.f;

	env->translation_matrix = identity_mat4();
	env->rotation_matrix = identity_mat4();

	translate_mat4(env->translation_matrix, &minus_b);
	rotate_y_mat4(env->rotation_matrix, env->y_auto_rotate_angle);

	delete_matrix(env->model_matrix);
	env->model_matrix = identity_mat4();
	multiply_mat4(env->translation_matrix, env->rotation_matrix, env->model_matrix);
	translate_mat4(env->model_matrix, &b);

	// printf("env->y_auto_rotate_angle : %f", env->y_auto_rotate_angle);

 	mvp = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp->value);

	glUseProgram(env->object_shader_program.id);
	render_vao(env->vao, GL_TRIANGLES, env->data.vertex_count);

	delete_matrix(mvp);
	delete_matrix(env->model_matrix);
	delete_matrix(env->translation_matrix);
	delete_matrix(env->rotation_matrix);

	//
	// PLAN
	//
	mvp = identity_mat4();
	env->model_matrix = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	// GL_TRUE indicates that is is row major matrix
	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);

	check_gl_error();

	glUseProgram(env->internal_object_shader_program.id);
	render_vao(env->plan_vao, GL_POINTS, 1);

	delete_matrix(mvp);

	// //
	// // AXIS
	// //

	// mvp = identity_mat4();
	// env->model_matrix = identity_mat4();

	// multiply_mat4(mvp, env->model_matrix, mvp);

	// multiply_mat4(mvp, env->view_matrix, mvp);

	// multiply_mat4(mvp, env->projection_matrix, mvp);

	// glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp->value);

	// glUseProgram(env->axis_shader_program.id);
	// render_vao(env->axis_vao, GL_POINTS, 1);
	
	// delete_matrix(mvp);
}
