#include "object_loading.h"

int			read_normal_vector(const char **tokens)
{
	t_vec3	normal;

	if (read_vec3(tokens, normal) < 0)
		read_object_error("A normal needs three arguments.");

  ft_lstadd(g_current_data->normals, ft_lstnew(&normal, sizeof(normal)));

  return (0);
}
