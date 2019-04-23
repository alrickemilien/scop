#include "libmatrix.h"

t_mat4	*rotate_x_mat4(t_mat4 *m, GLfloat amount)
{
	t_mat4	*rotation;
	GLfloat	*cell;

	cell = matrix_at(m, 1, 1);
	*cell = cos(amount);

	cell = matrix_at(m, 1, 2);
	*cell = sin(amount) * -1;

	cell = matrix_at(m, 2, 1);
	*cell = sin(amount);

	cell = matrix_at(m, 2, 2);
	*cell = cos(amount);

	rotation = identity_matrix(4, 4);

	if (m == NULL)
		return (rotation);

	multiply_matrix(m, rotation, m);

	return(m);
}
