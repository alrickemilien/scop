#include "libmatrix.h"

t_vec3	set_vec3(t_vec3 *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (*vector);
}
