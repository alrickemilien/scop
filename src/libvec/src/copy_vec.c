#include "libvec.h"

inline void			vec3_copy(t_vec3 *dest, const t_vec3 *src)
{
	memcpy(dest, src, sizeof(t_vec3));
}
