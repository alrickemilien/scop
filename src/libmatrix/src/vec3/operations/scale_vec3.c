#include "libmatrix.h"

t_vec3	scale_vec3(t_vec3 src, float factor)
{
	t_vec3 dest;

	dest.x = src.x * factor;
	dest.y = src.y * factor;
	dest.z = src.z * factor;
	return (dest);
}
