#include "libmatrix.h"

/*
** Fill the matrix with the value past as parameter
*/

void fill_matrix(t_matrix *m, void *value)
{
  size_t  i;

  i = 0;
  while (i < m->lines * m->columns)
  {
    memcpy(&m->value[i], value, sizeof(GLfloat));
    i++;
  }
}
