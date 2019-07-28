#include "libmatrix.h"

void	translate_mat4(
	t_mat4 *dest,
	const t_vec3 *amount)
{
	dest->value[12] += amount->x;
	dest->value[13] += amount->y;
	dest->value[14] += amount->z;
}
