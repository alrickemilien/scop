#include "libmatrix.h"

void			swap_vec3(t_vec3 **vector1, t_vec3 **vector2)
{
	t_vec3	*tmp;

	tmp = *vector1;
	*vector1 = *vector2;
	*vector2 = tmp;
}
