#include "libmatrix.h"

t_matrix	transpose_mat4(t_matrix *a)
{
	size_t	h;
	size_t	w;
	t_mat4	t;

	h = 0;
	while (h < 4)
	{
		w = 0;
		while (w < 4)
		{
			t.value[w * 4 + h] = a->value[h * 4 + w];
			w++;
		}
		h++;
	}
	memcpy(a->value, t.value, 16 * sizeof(GLfloat));
	return (*a);
}

t_matrix	transpose_to_mat4(const t_matrix *src, t_matrix *dest)
{
	size_t	h;
	size_t	w;

	h = 0;
	while (h < 4)
	{
		w = 0;
		while (w < 4)
		{
			dest->value[w * 4 + h] = src->value[h * 4 + w];
			w++;
		}
		h++;
	}
	return (*dest);
}
