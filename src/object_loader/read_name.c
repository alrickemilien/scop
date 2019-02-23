#include "object_loading.h"

int				read_name(t_obj_data *data, const t_token *tokens)
{
  if (data->name != NULL)
		return read_object_error("The object has multiple name.");

	data->name = strndup(tokens[0].cursor, tokens[0].size);

	return (0);
}
