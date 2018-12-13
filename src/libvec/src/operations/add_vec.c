#include "libvec.h"

float			vec3_dot(const t_vec3 *vector1, const t_vec3 *vector2)
{
	return (vector1->x * vector2->x + vector1->y * vector2->y
		+ vector1->z * vector2->z);
}

void			vec3_add(t_vec3 *vector, const t_vec3 *modifier)
{
	vector->x += modifier->x;
	vector->y += modifier->y;
	vector->z += modifier->z;
}

void			vec3_sub(t_vec3 *vector, const t_vec3 *modifier)
{
	vector->x -= modifier->x;
	vector->y -= modifier->y;
	vector->z -= modifier->z;
}

void			vec3_mult(t_vec3 *vector, float factor)
{
	vector->x *= factor;
	vector->y *= factor;
	vector->z *= factor;
}
