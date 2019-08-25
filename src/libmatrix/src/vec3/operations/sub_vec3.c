#include "libmatrix.h"

t_vec3	sub_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 dest;

	dest.x = a.x - b.x;
	dest.y = a.y - b.y;
	dest.z = a.z - b.z;
	return (dest);
}
