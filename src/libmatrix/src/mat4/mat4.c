#include "libmatrix.h"

t_mat4	*new_mat4(void)
{
	t_mat4	*matrix;

	if (NULL == (matrix = (t_matrix*)malloc(sizeof(t_matrix))))
		return (NULL);
	return (matrix);
}

t_mat4	*identity_mat4(void)
{
	t_mat4	*matrix;
	size_t	zero;
	size_t	i;

	matrix = new_mat4();
	if (matrix == NULL)
		return (NULL);
	zero = 0;
	fill_mat4(matrix, &zero);
	i = 0;
	while (i < 4)
	{
		matrix->value[i * 4 + i] = 1;
		i++;
	}
	return (matrix);
}
