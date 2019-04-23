#include "libmatrix.h"

t_mat4	*translate_mat4(t_mat4 *dest, const t_vec3 *amount)
{
	t_mat4	*translation;

	translation = identity_matrix(4, 4);

	translation->value[3] = amount->x;
	translation->value[7] = amount->y;
	translation->value[11] = amount->z;

	if (dest == NULL)
		return (translation);

	multiply_matrix(dest, translation, translation);

	return (translation);
}
