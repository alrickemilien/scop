#include "object_loader.h"

int				read_mtl(t_obj_data *data, const t_token *tokens)
{
  if (data->mtl != NULL)
		return read_object_error("The object has multiple mtl references.");;

	data->mtl = strndup(tokens[0].cursor, tokens[0].size);

	return (0);
}
