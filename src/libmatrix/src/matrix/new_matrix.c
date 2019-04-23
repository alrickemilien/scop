#include "libmatrix.h"

t_matrix  *new_matrix(size_t lines, size_t columns)
{
  t_matrix *matrix;

	if (!lines || !columns)
		return (NULL);

  if (NULL == (matrix = (t_matrix*)malloc(sizeof(t_matrix))))
    return (NULL);

  matrix->lines = lines;
  matrix->columns = columns;

  matrix->inverse = 0;

  return (matrix);
}
