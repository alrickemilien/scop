#include "libmatrix.h"

t_matrix *get_minor(t_matrix *a, size_t line, size_t columns)
{
	t_matrix	*minor;
  size_t		x;
  size_t		y;
  size_t		i;
  size_t		j;

  minor = new_matrix(a->lines - 1, a->columns - 1);

  if(minor == NULL) {
		return NULL;
	}

	x = 0;
	i = 0;
	while (i < a->lines)
	{
		if (i == line)
			x--;

		y = 0;
		j = 0;
		while (j < a->columns)
		{
			if(i != line && j != columns) {
				memcpy(
					&minor->value[x * a->columns + y],
					&a->value[i * a->columns + j],
					sizeof(GLfloat));
				y++;
			}

			j++;
		}

		i++;
		x++;
	}

	return (minor);
}
