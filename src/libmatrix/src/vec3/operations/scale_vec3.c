#include "libmatrix.h"

void	scale_vec3(t_vec3 *vector, float factor)
{
	vector->x *= factor;
	vector->y *= factor;
	vector->z *= factor;
}
