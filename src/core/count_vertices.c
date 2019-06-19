#include "scop.h"

void	count_vertices(t_mesh *data)
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

// void	count_vertices(t_mesh *data)
// {
// 	size_t	count;
// 	size_t	poly_length;
// 	t_list	*x;

// 	x = data->polygons;
// 	count = 0;
// 	while (x)
// 	{
// 		poly_length = ft_lstlen(((t_polygon*)x->content)->vertices);

// 		if (poly_length != 3)
// 			read_object_error("Scop can only handle triangle shapes.");
// 		else
// 			count += poly_length;

// 		x = x->next;
// 	}

// 	data->vertex_count = count;
// }