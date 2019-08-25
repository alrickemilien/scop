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

t_mat4	scale_mat4(t_mat4 *a, GLfloat scalar)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		a->value[i] = (GLfloat)a->value[i] * scalar;
		i++;
	}
	return (*a);
}

t_mat4	scale_to_mat4(const t_mat4 *src, t_mat4 *dest, GLfloat scalar)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		dest->value[i] = (GLfloat)src->value[i] * scalar;
		i++;
	}
	return (*dest);
}
