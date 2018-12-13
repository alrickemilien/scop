#include "libvec.h"

void			normalize_vec(t_vec3 *vector)
{
	float	magn;

	magn = vec3_magnitude(vector);

  vector->x = vector->x / magn;
	vector->y = vector->y / magn;
	vector->z = vector->z / magn;
}
