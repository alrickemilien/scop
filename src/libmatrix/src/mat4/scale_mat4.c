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

void	scale_mat4(t_mat4 *a, GLfloat scalar)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		a->value[i] = (GLfloat)a->value[i] * scalar;
		i++;
	}
}
