#include "libmatrix.h"

void	mat4_on_vec3(t_vec3 *v, const t_mat4 *m)
{
	GLfloat	w;

	v->x = m->value[0] * v->x
		+ m->value[4] * v->y
		+ m->value[8] * v->z
		+ m->value[12];
	v->y = m->value[1] * v->x
		+ m->value[5] * v->y
		+ m->value[9] * v->z
		+ m->value[13];
	v->z = m->value[2] * v->x
		+ m->value[6] * v->y
		+ m->value[10] * v->z
		+ m->value[14];
	w = m->value[3] * v->x
		+ m->value[7] * v->y
		+ m->value[11] * v->z
		+ m->value[15];
	*v = (t_vec3){v->x / w, v->y / w, v->z / w};
}
