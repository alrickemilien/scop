#include "libmatrix.h"

int				is_origin_vec3(const t_vec3 *vector)
{
	return (vector->x == 0 && vector->y == 0 && vector->z == 0);
}
