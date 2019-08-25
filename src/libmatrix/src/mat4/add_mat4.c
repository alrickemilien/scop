#include "libmatrix.h"

t_matrix	add_mat4(t_matrix *a, const t_matrix *b)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		a->value[i] = a->value[i] + b->value[i];
		i++;
	}
	return (*a);
}

t_matrix	add_to_mat4(const t_matrix *a, const t_matrix *b, t_matrix *result)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		result->value[i] = a->value[i] + b->value[i];
		i++;
	}
	return (*a);
}
