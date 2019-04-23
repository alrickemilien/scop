#include "libmatrix.h"

int get_determinant(t_matrix *a)
{
	int det;
	t_matrix *tmp;
	size_t		i;

	if (a->lines == 1 && a->columns == 1) {
		return (a->value[0]);
	}

  det = 0;
	i = 0;
	while (i < a->columns)
	{
	    tmp = get_minor(a, 0, i);
	    det += ((int)a->value[i])
						* (pow(-1, 2 + i)) * (get_determinant(a));
	    delete_matrix(tmp);
			i++;
	}

  return (det);
}
