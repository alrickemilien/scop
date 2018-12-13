#include "libvec.h"

void			scale_vec(t_vec3 *vector, float factor)
{
	vector->x *= factor;
	vector->y *= factor;
	vector->z *= factor;
}
