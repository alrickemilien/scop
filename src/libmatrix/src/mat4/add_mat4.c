#include "libmatrix.h"

void	add_mat4(t_matrix *a, t_matrix *b, t_matrix *result)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		result->value[i] = a->value[i] + b->value[i];
		i++;
	}
}
