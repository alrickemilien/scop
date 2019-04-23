#include "libmatrix.h"

void copy_matrix(t_matrix *a, t_matrix *destination)
{
  if (destination == NULL)
    return;

	if(a->lines != destination->lines && a->columns != destination->columns)
		return ;

	memcpy(destination->value, a->value, a->columns * a->lines * sizeof(GLfloat));
}
