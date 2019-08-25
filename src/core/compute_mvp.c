#include "scop.h"

t_mat4		*compute_mvp(t_software_environ *env, t_mat4 *mvp)
{
	multiply_mat4(mvp, &env->model_matrix);
	multiply_mat4(mvp, &env->view_matrix);
	multiply_mat4(mvp, &env->projection_matrix);
	return (mvp);
}