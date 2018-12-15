#include "object_loading.h"

int			read_color(t_obj_data *data, const t_token *token)
{
	t_vec2	new_color;

  if (!check_tokens_number(token, 2))
		read_object_error("A texture needs two arguments.");

  new_color.x = atof(&token->cursor[0]);
	new_color.y = atof(&token->cursor[1]);

	ft_lstadd(data->uvs, ft_lstnew(&new_color, sizeof(t_vec2)));

  return (0);
}
