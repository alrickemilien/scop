#include "libmatrix.h"

/*
** Returns true when matrix have the same size
*/

static bool are_matrix_same_size(t_matrix *a, t_matrix *b)
{
	return (a->lines == b->lines && a->columns == b->columns);
}

int multiply_matrix(t_matrix *a, t_matrix *b, t_matrix *result)
{
  size_t x;
  size_t y;
  size_t i;
  size_t j;
  size_t k;
  size_t columns;

	t_matrix *tmp;

  if (!are_matrix_same_size(a, b) || !are_matrix_same_size(a, result))
		return (NOT_SAME_SIZE);

  i = 0;

	tmp = new_matrix(a->lines, b->columns);

  fill_matrix(tmp, &i);

	if (tmp == NULL)
		return (CAN_NOT_CREATE_MATRIX);

	x = 0;
  while (i < a->lines)
  {
    y = 0;
    k = 0;
    columns = b->columns;
    while (columns > 0)
    {
			j = 0;
      while (j < a->columns)
      {
        tmp->value[x * a->columns + y]
          += a->value[i * a->columns + j] * b->value[j * a->columns + k];
        j++;
      }
      columns--;
      k++;
      y++;
    }

    i++;
    x++;
  }

	memcpy(result->value, tmp->value, a->lines * a->columns * sizeof(GLfloat));

	delete_matrix(tmp);

	return (LIBMATRIX_NO_ERROR);
}
