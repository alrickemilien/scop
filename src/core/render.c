#include "scop.h"

static void render_vao(GLuint vao, GLenum render_style, size_t vertex_number) {
	glBindVertexArray(vao);
	glDrawArrays(render_style, 0, vertex_number);
}

static void apply_rotation(t_software_environ *env) {
	t_vec3 minus_b;
	t_vec3 b;

	b = compute_object_barycentre(env->data.positions);

	// b = (t_vec3){4.f, 4.f, 4.f};

	minus_b = (t_vec3){-b.x, -b.y, -b.z};
 
	printf("BARYCENTRE : .x %f .y %f .z %f \n", b.x, b.y, b.z);
	
	env->y_auto_rotate_angle += 0.5f;
	if (env->y_auto_rotate_angle >= 360.f)
		env->y_auto_rotate_angle = 30.f;

	env->translation_matrix = identity_mat4();
	env->rotation_matrix = identity_mat4();
	
	rotate_y_mat4(env->rotation_matrix, env->y_auto_rotate_angle);
	
	translate_mat4(env->translation_matrix, &minus_b);

	env->model_matrix = identity_mat4();
	multiply_mat4(env->rotation_matrix, env->translation_matrix, env->model_matrix);

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			printf("%.3f ", env->model_matrix->value[j * 4 + i]);
		}
		printf("\n");
	}
	printf("\n");
}

t_mat4 *compute_mvp(t_software_environ *env) {
	t_mat4 *mvp;

 	mvp = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	return (mvp);
}

void		render(t_software_environ *env)
{
	t_mat4 *mvp;

	apply_rotation(env);

	mvp = compute_mvp(env);

	glUseProgram(env->object_shader_program.id);

	glUniformMatrix4fv(env->mvp_uni, 1, GL_FALSE, mvp->value);

	check_gl_error();

	render_vao(env->vao, GL_TRIANGLES, env->data.vertex_count);

	delete_matrix(mvp);
	delete_matrix(env->model_matrix);
	delete_matrix(env->translation_matrix);
	delete_matrix(env->rotation_matrix);

	//
	// PLAN
	//

	env->model_matrix = identity_mat4();

	mvp = compute_mvp(env);

	glUseProgram(env->internal_object_shader_program.id);

	// GL_TRUE indicates that is is row major matrix
	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);

	check_gl_error();

	render_vao(env->plan_vao, GL_POINTS, 1);

	delete_matrix(mvp);
	delete_matrix(env->model_matrix);

	//
	// AXIS
	//

	env->model_matrix = identity_mat4();

	mvp = compute_mvp(env);

	glUseProgram(env->axis_shader_program.id);

	glUniformMatrix4fv(env->internal_object_mvp_uni, 1, GL_FALSE, mvp->value);

	render_vao(env->axis_vao, GL_POINTS, 1);
	
	delete_matrix(mvp);
	delete_matrix(env->model_matrix);
}
