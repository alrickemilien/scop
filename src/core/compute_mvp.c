#include "scop.h"

t_mat4		*compute_mvp(t_software_environ *env)
{
	t_mat4	*mvp;

 	mvp = identity_mat4();

	multiply_mat4(mvp, env->model_matrix, mvp);

	multiply_mat4(mvp, env->view_matrix, mvp);

	multiply_mat4(mvp, env->projection_matrix, mvp);

	return (mvp);
}