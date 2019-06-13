#include "libmatrix.h"

t_vec3			return_sub_vec3(t_vec3 vector, t_vec3 modifier)
{
    t_vec3 v;
	v.x = vector.x -= modifier.x;
	v.y = vector.y -= modifier.y;
	v.z = vector.z -= modifier.z;

    return (v);
}
