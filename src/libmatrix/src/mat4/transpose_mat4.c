#include "libmatrix.h"

int get_transpose(t_matrix *a, t_matrix *transpose)
{
	size_t i;
	size_t j;

  if(transpose == NULL)
		return (CAN_NOT_CREATE_MATRIX);

	i = 0;
	while (i < a->lines) {
		j = 0;
		while (j < a->columns) {
			transpose->value[i * a->lines + j] = a->value[j * a->lines + i % a->columns];
			j++;
		}
		i++;
	}

	return (LIBMATRIX_NO_ERROR);
}


t_mat4	*mat4_transpose(t_matrix *a)
{
	size_t		h;
	size_t		w;
	t_mat4		*t;

	t = new_mat4(void);

	h = 0;
	while (h < 4)
	{
		w = 0;
		while (w < 4) {
			t->values[w * 4 + h] = m->values[h * 4 + w];
			w++;
		}
		h++;
	}

	return (t);
}