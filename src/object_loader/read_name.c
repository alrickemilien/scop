#include "object_loader.h"

int				read_name(t_mesh *data, const t_token *tokens)
{
  if (data->name != NULL)
		return read_object_error("The object has multiple name.");

	data->name = strndup(tokens[0].cursor, tokens[0].size);

	return (0);
}
