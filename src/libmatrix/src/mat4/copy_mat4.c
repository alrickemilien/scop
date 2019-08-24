#include "libmatrix.h"

t_mat4	copy_mat4(t_mat4 *src, t_mat4 *destination)
{
	memcpy(destination->value, src->value, 16 * sizeof(GLfloat));
    return (*destination);
}
