#include "libmatrix.h"

t_mat4 *perspective_mat4(
	GLfloat fov,
	GLfloat aspect,
	GLfloat near_plane,
	GLfloat far_plane)
{
	t_mat4			*ret;

	ret = identity_mat4();
	
	float	tan_half_fov;
	
	tan_half_fov = tanf(fov / 2.0f);

	ret->value[0] = 1.0f / (aspect * tan_half_fov);
	ret->value[5] = 1.0f / (tan_half_fov);
	ret->value[10] = (far_plane + near_plane) / (far_plane - near_plane) * -1;
	ret->value[11] = -1.0f;
	ret->value[14] = (2.0f * far_plane * near_plane)
	/ (far_plane - near_plane) * -1;

	return (ret);
}