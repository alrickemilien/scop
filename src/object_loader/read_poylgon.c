#include <string.h>
#include "object_loading.h"

static char **split_polygon_component() {

}

static int		read_polygon_components(
					const char **tokens,
					t_polygon *new_polygon)
{
	int			i;
	bool			is_texture_set;
	char		**ctokens;

	i = 0;
	if (!check_tokens_number(tokens, 3))
		read_object_error("A face must declare at least three vertices.");
	while (tokens[i])
	{
		is_texture_set = false;

    if (strstr(tokens[i], "//"))
			is_texture_set = true;

    ctokens = ft_split(tokens[i], "/\n");

    if (!read_vertex((const char **)ctokens, is_texture_set, new_polygon->vertices))
		{
			ft_free_tab(ctokens);
			return (-1);
		}

    i+;

    ft_free_tab(ctokens);
	}
	return (0);
}

/*
** Read following polygon schema in object file :
** f 1381//17765 9428//17765 1382//17765
** f 1381//17765 9428//17765 1382//17765
** ...
*/
int				read_poylgon(const char **tokens)
{
	t_polygon	*new_polygon;

	if (!(new_polygon = malloc(sizeof(t_polygon))))
		return (-1);

  new_polygon->vertices = new_lst();

  if (!parse_polygon_components(tokens, new_polygon))
	{
		free(new_polygon);
		return (-1);
	}

  lst_push_back(g_current_data->polygons, new_polygon);

  return (0);
}
