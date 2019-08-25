#include "libmatrix.h"

t_vec3	add_vec3(t_vec3 vector, t_vec3 modifier)
{
	t_vec3 dest;

	dest.x = vector.x + modifier.x;
	dest.y = vector.y + modifier.y;
	dest.z = vector.z + modifier.z;
	return (dest);
}
