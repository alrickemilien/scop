#include "libmatrix.h"

t_matrix  *identity_matrix(size_t lines, size_t columns)
{
  t_matrix *matrix;
  size_t zero;
  size_t i;

  matrix = new_matrix(lines, columns);

	if (matrix == NULL)
		return (NULL);

	zero = 0;
	fill_matrix(matrix, &zero);

  i = 0;
  while (i < matrix->columns)
  {
		matrix->value[i * matrix->columns + i] = 1;
    i++;
  }

  return (matrix);
}
