#include "scop.h"

void	count_vertices(t_obj_data *data)
{
	size_t	count;
	t_list	*x;

	x = data->polygons;
	count = 0;
	while (x)
	{
		// read_object_error("Scop can only handle triangle shapes.");
		count += ft_lstlen(((t_polygon*)x->content)->vertices);

		x = x->next;
	}

	data->vertex_count = count;
}
