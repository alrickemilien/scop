#include "libmatrix.h"

void	normalize_vec3(t_vec3 *vector)
{
	float	magnitude;

	magnitude = magnitude_vec3(vector);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
	vector->z = vector->z / magnitude;
}
