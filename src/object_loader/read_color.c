#include "object_loading.h"

int			read_color(const char **tokens)
{
	t_vec2	new_color;

  if (!tokens_are_enough(tokens, 2))
		read_object_error("A texture needs two arguments.");

  new_color->x = atof(tokens[0]);
	new_color->y = atof(tokens[1]);

	ft_lstadd(g_current_data->uvs, ft_lstnew(&new_color, sizeof(t_vec2)));

  return (0);
}
