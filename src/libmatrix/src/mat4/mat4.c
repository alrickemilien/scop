#include "libmatrix.h"

t_mat4	identity_mat4(t_mat4 *m)
{
	size_t	zero;
	size_t	i;

	zero = 0;
	fill_mat4(m, &zero);
	i = 0;
	while (i < 4)
	{
		m->value[i * 4 + i] = 1;
		i++;
	}
	return (*m);
}
