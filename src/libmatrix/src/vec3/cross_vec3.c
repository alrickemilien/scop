#include "libmatrix.h"

void			cross_vec3(t_vec3 *vector1, const t_vec3 *vector2)
{
	GLfloat	x;
	GLfloat	y;
	GLfloat	z;

	x = vector1->y * vector2->z - vector1->z * vector2->y;
	y = vector1->z * vector2->x - vector1->x * vector2->z;
	z = vector1->x * vector2->y - vector1->y * vector2->x;
	vector1->x = x;
	vector1->y = y;
	vector1->z = z;
}
