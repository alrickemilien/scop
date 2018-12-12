#include "object_loading.h"

int			read_position(const char **tokens)
{
	t_vec3	*new_position;

	if (!(new_position = malloc(sizeof(t_vec3))))
		return (0);
	else if (parse_vec3(tokens, new_position) < 0)
	{
		free(new_position);
		return (0);
	}

  lst_push_back(g_current_data->positions, new_position);

  return (1);
}
