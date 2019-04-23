#include "libmatrix.h"

int inverse_matrix(t_matrix *a)
{
  t_matrix *transpose;
  t_matrix *adjugate;
  t_matrix *current_minor;
  size_t i;
  size_t j;

  if(a->determinant == 0.0) {
		return (NO_INVERSE);
	}

	transpose = new_matrix(a->lines, a->columns);
	adjugate = new_matrix(a->lines, a->columns);

	get_transpose(a, transpose);

  i = 0;
  while (i < transpose->lines)
  {
    j = 0;
    while (j < transpose->columns)
    {
      current_minor = get_minor(transpose, i, j);

      adjugate->value[i * transpose->columns + j]
        = pow(-1.0, (double)i + (double)j) * get_determinant(current_minor);

      delete_matrix(current_minor);
      j++;
    }
    i++;
  }

  delete_matrix(transpose);

	a->inverse = adjugate;

  multiply_matrix_with_scalar(a->inverse, 1 / a->determinant);

	return (LIBMATRIX_NO_ERROR);
}
