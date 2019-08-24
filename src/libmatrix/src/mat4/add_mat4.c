#include "libmatrix.h"

t_matrix    add_mat4(t_matrix *a, t_matrix *b, t_matrix *result)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		result->value[i] = a->value[i] + b->value[i];
		i++;
	}
    return (*result);
}

t_matrix    add_to_mat4(t_matrix *a, t_matrix *b, t_matrix *result)
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
