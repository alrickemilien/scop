#include "libvec.h"

float			magnitude_vec(const t_vec3 *vector)
{
	return (sqrtf(
    powf(vector->x, 2)
    + powf(vector->y, 2)
		+ powf(vector->z, 2)));
}
