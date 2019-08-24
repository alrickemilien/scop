#include "libmatrix.h"

t_vec3	return_cross_vec3(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	v;

	v.x = vector1.y * vector2.z - vector1.z * vector2.y;
	v.y = vector1.z * vector2.x - vector1.x * vector2.z;
	v.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (v);
}
