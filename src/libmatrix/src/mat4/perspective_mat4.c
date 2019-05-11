#include "libmatrix.h"

/*
** Provides 2 types of projection matrixes
*/

t_mat4 *orthograhic_mat4(
	GLfloat fov,
	GLfloat aspect_ratio,
	GLfloat znear,
	GLfloat zfar)
{
	t_mat4			*ret;
	GLfloat			l;
	GLfloat			r;
	GLfloat			t;
	GLfloat			b;
	GLfloat			MAX;

	(void)fov;

	// float maxx = std::max(fabs(minCamera.x), fabs(maxCamera.x));
	// float maxy = std::max(fabs(minCamera.y), fabs(maxCamera.y));
	// float max = std::max(maxx, maxy); 
	MAX = 1000;
 
    r = MAX * aspect_ratio;
	t = MAX;
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

t_mat4 *perspective_mat4(
	GLfloat fov,
	GLfloat aspect_ratio,
	GLfloat znear,
	GLfloat zfar)
{
	t_mat4			*ret;

	ret = identity_mat4();
	
	GLfloat	tan_half_fov;

	tan_half_fov = tanf(fov * 0.5f * M_PI / 180.0f);

	ret->value[0] = 1.0f / tan_half_fov / aspect_ratio;
	ret->value[5] = 1.0f / tan_half_fov;
	ret->value[10] = -(zfar + znear) / (zfar - znear);
	ret->value[11] = -1.0f;
	ret->value[14] = -2.0f * zfar * znear / (zfar - znear);

	return (ret);
}

/*
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
*/