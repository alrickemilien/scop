#include "libvec.h"

inline int				is_vec_origin(const t_vec3 *vector)
{
	return (vector->x == 0 && vector->y == 0 && vector->z == 0);
}
