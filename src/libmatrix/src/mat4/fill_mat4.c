#include "libmatrix.h"

/*
** Fill the matrix with the value past as parameter
*/

void	fill_mat4(t_mat4 *m, void *value)
{
	size_t	i;

	i = 0;
	while (i < 16)
		memcpy(&m->value[i++], value, sizeof(GLfloat));
}
