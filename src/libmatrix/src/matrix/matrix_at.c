#include "libmatrix.h"

GLfloat   *matrix_at(t_matrix *m, size_t line, size_t column)
{
  if (line * m->columns + column > m->lines * m->columns)
    return (NULL);

  return &m->value[line * m->columns + column];
}
