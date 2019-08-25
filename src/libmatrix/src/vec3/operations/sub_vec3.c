#include "libmatrix.h"

t_vec3	sub_vec3(t_vec3 *vector, const t_vec3 *modifier)
{
	vector->x -= modifier->x;
	vector->y -= modifier->y;
	vector->z -= modifier->z;
	return (*vector);
}

t_vec3	sub_to_vec3(const t_vec3 *a, const t_vec3 *b, t_vec3 *dest)
{
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
	dest->z = a->z - b->z;
	return (*dest);
}
