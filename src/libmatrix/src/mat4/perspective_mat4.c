#include "libmatrix.h"

static const GLfloat g_max = 1000;

/*
** Provides 2 types of projection matrixes
*/

t_mat4	*orthograhic_mat4(
	GLfloat fov,
	GLfloat aspect_ratio,
	GLfloat znear,
	GLfloat zfar)
{
	t_mat4	*ret;
	GLfloat	l;
	GLfloat	r;
	GLfloat	t;
	GLfloat	b;

	(void)fov;

	// float maxx = std::max(fabs(minCamera.x), fabs(maxCamera.x));
	// float maxy = std::max(fabs(minCamera.y), fabs(maxCamera.y));
	// float max = std::max(maxx, maxy); 
 
    r = g_max * aspect_ratio;
	t = g_max;
    l = -r;
	b = -t;

	ret = identity_mat4();

	ret->value[0] = 2.0f / (r - l);
	ret->value[5] = 2.0f / (t - b);
	ret->value[10] = -2.0f / (zfar - znear);
	ret->value[12] = -(r + l) / (r - l);
	ret->value[12] = -(t + b) / (t - b);
	ret->value[12] = -(zfar + znear) / (zfar - znear);
	ret->value[15] = 1.0f;

	return (ret);
}


/*
** Creates a projection matrix like gluPerspective or glFrustum.
** Upload to your shader as usual.
*/

t_mat4	*perspective_mat4(
	GLfloat fov,
	GLfloat aspect_ratio,
	GLfloat znear,
	GLfloat zfar)
{
	t_mat4	*ret;
	GLfloat	tan_half_fov;

	ret = identity_mat4();

	tan_half_fov = tanf(fov * 0.5f * M_PI / 180.0f);

	ret->value[0] = 1.0f / tan_half_fov / aspect_ratio;
	ret->value[5] = 1.0f / tan_half_fov;
	ret->value[10] = -(zfar + znear) / (zfar - znear);
	ret->value[11] = -1.0f;
	ret->value[14] = -2.0f * zfar * znear / (zfar - znear);

	return (ret);
}