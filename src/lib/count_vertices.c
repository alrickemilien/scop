# include "scop.h"

void	count_vertices(t_obj_data *data)
{
	size_t	count;
	size_t	poly_length;
	t_list	*iter;

	iter = (t_list*)data->polygons;
	count = 0;
	while (iter)
	{
		poly_length = ft_lstlen(((t_polygon*)iter->content)->vertices);
		if (poly_length != 3)
			read_object_error("Scop can only handle triangle shapes.");

		count += poly_length;

		iter = iter->next;
	}

	data->vertex_count = count;
}
