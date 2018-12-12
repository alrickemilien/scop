#include "object_loading.h"

int			read_normal_vector(const char **tokens)
{
	t_vec3	*normal;

	if (!(normal = malloc(sizeof(t_vec3))))
		return (-1);
	else if (read_vec3(tokens, normal) < 0)
	{
		free(normal);
		read_object_error("A normal needs three arguments.");
	}

  lst_push_back(g_current_data->normals, normal);

  return (0);
}
