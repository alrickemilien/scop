#include "libmatrix.h"

static const float	g_degtorad = 3.141593f / 180.0f;

t_mat4	rotate_x_mat4(t_mat4 *m, GLfloat angle)
{
	GLfloat	alpha;

	alpha = angle * g_degtorad;
	m->value[5] = cosf(alpha);
	m->value[6] = sinf(alpha);
	m->value[9] = -sinf(alpha);
	m->value[10] = cosf(alpha);
	return (*m);
}

t_mat4	rotate_y_mat4(t_mat4 *m, GLfloat angle)
{
	GLfloat	alpha;

	alpha = angle * g_degtorad;
	m->value[0] = cosf(alpha);
	m->value[2] = -sinf(alpha);
	m->value[8] = sinf(alpha);
	m->value[10] = cosf(alpha);
	return (*m);
}

t_mat4	rotate_z_mat4(t_mat4 *m, GLfloat angle)
{
	GLfloat	alpha;

	alpha = angle * g_degtorad;
	m->value[0] = cosf(alpha);
	m->value[1] = sinf(alpha);
	m->value[4] = -sinf(alpha);
	m->value[5] = cosf(alpha);
	return (*m);
}
