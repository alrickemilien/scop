#include "libmatrix.h"

t_matrix  *new_matrix_from_raw(
  const GLfloat *raw,
  size_t lines,
  size_t columns)
{
  t_matrix *matrix;
  size_t    i;
  size_t    j;

  matrix = new_matrix(lines, columns);

  if (NULL == matrix)
    return (NULL);

  i = 0;
  while (i < matrix->lines)
  {
    j = 0;
    while (j < matrix->columns)
    {
      memcpy(
        &matrix->value[i * matrix->columns + j],
        &raw[i * matrix->columns + j],
        sizeof(GLfloat));
      j++;
    }
    i++;
  }

  return (matrix);
}
