#include "libmatrix.h"

GLfloat magnitude_vec3(const t_vec3 *vector)
{
	return (sqrtf(
    powf(vector->x, 2)
    + powf(vector->y, 2)
		+ powf(vector->z, 2)));
}
