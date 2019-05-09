#include "libmatrix.h"
/*
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
*/

/*
** Creates a projection matrix like gluPerspective or glFrustum.
** Upload to your shader as usual.
*/

t_mat4 *perspective_mat4(
	GLfloat fov,
	GLfloat aspect,
    GLfloat znear,
	GLfloat zfar)
{
		GLfloat top;
		GLfloat right;

		t_mat4 *ret;
		ret = identity_mat4();

		top = tanf(deg_to_rad(fov) / 2.0f) * znear;
		right = top * aspect;

		ret->value[0] = znear / right;
		ret->value[5] = znear / top;
		ret->value[10] = -(zfar + znear) / (zfar - znear);
		ret->value[11] = -2.0f * zfar * znear / (zfar - znear);
		ret->value[14] = -1.0f;

    return ret;

}