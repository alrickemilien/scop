#include "libmatrix.h"

void	translate_mat4(t_mat4 *dest, const t_vec3 *amount)
{
	t_mat4	*translation;

	translation = identity_mat4();

	translation->value[3] = amount->x;
	translation->value[7] = amount->y;
	translation->value[11] = amount->z;

	multiply_mat4(dest, translation, translation);

	delete_matrix(translation);
}
