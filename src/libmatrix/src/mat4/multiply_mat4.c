#include "libmatrix.h"

/*
** Multiply row major matrix between them
*/

int	multiply_mat4(t_matrix *a, t_matrix *b, t_matrix *result)
{
	size_t	h;
	size_t	w;
	size_t	z;
	t_mat4	*tmp;

	tmp = new_mat4();
	if (tmp == NULL)
		return (CAN_NOT_CREATE_MATRIX);
	h = 0;
	while (h < 4)
	{
		w = 0;
		while (w < 4)
		{
			z = 0;
			tmp->value[h * 4 + w] = 0;
			while (z < 4)
			{
				tmp->value[h * 4 + w] +=
					a->value[h * 4 + z] * b->value[z * 4 + w];
				z++;
			}
			w++;
		}
		h++;
	}
	memcpy(result->value, tmp->value, 16 * sizeof(GLfloat));
	delete_matrix(tmp);
	return (LIBMATRIX_NO_ERROR);
}
