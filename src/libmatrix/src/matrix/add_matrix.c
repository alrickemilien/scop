#include "libmatrix.h"

int     add_matrix(t_matrix *a, t_matrix *b, t_matrix *result)
{
  size_t  i;

  if (a->lines != b->lines && a->columns != b->columns)
		return (NOT_SAME_SIZE);

  i = 0;
  while (i < a->lines * a->columns)
  {
		result->value[i] = a->value[i] + b->value[i];

    i++;
  }

  return (LIBMATRIX_NO_ERROR);
}
