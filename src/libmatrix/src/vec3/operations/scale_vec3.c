#include "libmatrix.h"

t_vec3	scale_vec3(t_vec3 *vector, float factor)
{
	vector->x *= factor;
	vector->y *= factor;
	vector->z *= factor;
	return (*vector);
}

t_vec3	scale_to_vec3(t_vec3 *src, t_vec3 *dest, float factor)
{
	dest->x = src->x * factor;
	dest->y = src->y * factor;
	dest->z = src->z * factor;
	return (*dest);
}
