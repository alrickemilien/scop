#include "libmatrix.h"

t_vec3	copy_vec3(t_vec3 *dest, const t_vec3 *src)
{
	memcpy(dest, src, sizeof(t_vec3));
	return (*dest);
}
