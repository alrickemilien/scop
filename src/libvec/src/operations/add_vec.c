#include "libvec.h"

void			add_vec(t_vec3 *vector, const t_vec3 *modifier)
{
	vector->x += modifier->x;
	vector->y += modifier->y;
	vector->z += modifier->z;
}
