#include "libmatrix.h"

/*
** Multiply a matrix by a scalar
** 1 1 1 1
** 1 1 1 1
** 1 1 1 1
** 1 1 1 1
** x 2.5 becomes
** 2.5 2.2 2.5 2.5
** 2.5 2.2 2.5 2.5
** 2.5 2.2 2.5 2.5
** 2.5 2.2 2.5 2.5
*/

void multiply_matrix_with_scalar(t_matrix *a, GLfloat scalar)
{
  size_t  i;

  i = 0;
  while (i < a->lines * a->columns)
  {
      a->value[i] = (GLfloat)a->value[i] * scalar;
      i++;
  }
}
