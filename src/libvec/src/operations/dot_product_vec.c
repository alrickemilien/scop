#include "libvec.h"

float			dot_product_vec(const t_vec3 *vector1, const t_vec3 *vector2)
{
	return (vector1->x * vector2->x
				+ vector1->y * vector2->y
				+ vector1->z * vector2->z);
}
