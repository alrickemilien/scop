#include "libmatrix.h"

t_vec3    normalize_vec3(t_vec3 *vector)
{
	float	magnitude;

	magnitude = magnitude_vec3(vector);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
	vector->z = vector->z / magnitude;
	return (*vector);
}

t_vec3  normalize_to_vec3(const t_vec3 *vector, t_vec3 *dest)
{
	float	magnitude;

	magnitude = magnitude_vec3(vector);
	*dest = (t_vec3){
	    vector->x / magnitude,
	    vector->y / magnitude,
	    vector->z / magnitude,
    };
    return (*dest);
}