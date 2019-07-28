#include "libmatrix.h"

void	transpose_mat4(t_matrix *a)
{
	size_t	h;
	size_t	w;
	t_mat4	*t;

	t = identity_mat4();
	h = 0;
	while (h < 4)
	{
		w = 0;
		while (w < 4) {
			t->value[w * 4 + h] = a->value[h * 4 + w];
			w++;
		}
		h++;
	}
	memcpy(a->value, t->value, 16 * sizeof(GLfloat));
	delete_matrix(t);
}