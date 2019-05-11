#include "libmatrix.h"

void copy_mat4(t_mat4 *a, t_mat4 *destination)
{
	memcpy(destination->value, a->value, 16 * sizeof(GLfloat));
}
