#include "libmatrix.h"

void  delete_matrix(t_matrix *matrix)
{
  if (matrix->inverse) {
    delete_matrix(matrix->inverse);
  }

	free(matrix);
}
