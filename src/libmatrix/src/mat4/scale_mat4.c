#include "libmatrix.h"

t_mat4	*scale_mat4(GLfloat amount)
{
  t_mat4	*m;

	m = identity_matrix(4, 4);

	if (!m)
		return (NULL);

	m->value[0] = amount;
	m->value[5] = amount;
	m->value[10] = amount;

  return (m);
}
