#include "libmatrix.h"

/*
** Return allocated vec2
*/

t_vec2	*new_vec2(
		GLfloat x,
		GLfloat y)
{
	t_vec2	*v;

	v = (t_vec2*)malloc(sizeof(t_vec2));
	v->x = x;
	v->y = y;
	return (v);
}
