#include "scop.h"

bool			is_vertex_same(
		const void *a,
		const void *b)
{
	t_vertex	*va;
	t_vertex	*vb;

	va = (t_vertex*)a;
	vb = (t_vertex*)b;
	if (va->position_index == vb->position_index
		&& va->normal_index == vb->normal_index)
		return (true);
	return (false);
}
