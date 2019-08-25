#include "libmatrix.h"

t_vec3  normalize_vec3(t_vec3 vector)
{
	float	magnitude;
	t_vec3	dest;

	magnitude = magnitude_vec3(&vector);
	dest = (t_vec3){
	    vector.x / magnitude,
	    vector.y / magnitude,
	    vector.z / magnitude,
    };
    return (dest);
}