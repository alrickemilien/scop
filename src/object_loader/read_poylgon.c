#include <string.h>
#include "object_loading.h"

static int		read_polygon_components(
          t_obj_data *data,
					const t_token *tokens,
					t_polygon *new_polygon)
{
	int			i;
	bool			is_texture_set;
	t_token *ctokens;

	i = 0;
	if (!check_tokens_number(tokens, 3))
		read_object_error("A face must declare at least three vertices.");
	while (tokens[i].cursor)
	{
		is_texture_set = false;

    if (strstr(tokens[i].cursor, "//"))
			is_texture_set = true;

    ctokens = split_into_tokens(tokens[i].cursor, "\\");

    if (!read_vertex(data, (const t_token *)ctokens, is_texture_set, new_polygon))
		{
			free(ctokens);
			return (-1);
		}

    i++;

    free(ctokens);
	}
	return (0);
}

/*
** Read following polygon schema in object file :
** f 1381//17765 9428//17765 1382//17765
** f 1381//17765 9428//17765 1382//17765
** ...
*/
int				read_polygon(t_obj_data *data, const t_token *tokens)
{
	t_polygon	new_polygon;

  if (!read_polygon_components(data, tokens, &new_polygon))
		return (-1);

  ft_lstadd(data->polygons,
		ft_lstnew(&new_polygon, sizeof(t_polygon)));

  return (0);
}
