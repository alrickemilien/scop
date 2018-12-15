#include <string.h>
#include "object_loading.h"

static char **split_polygon_components(const char *line) {
  size_t i;
  char   **array;

  i = 0;
  while (line[i] && !is_printable(line[i]))
    i++;

  if (NULL == (array = malloc(sizeof(char*) * (i + 1))))
    return (NULL);

  array[i] = 0;

  i = 0;
  while(line[i]) {
    while (line[i] && !is_printable(line[i]) && line[i] == '/')
      i++;

    memcpy(array[i], line + i, sizeof(char*));

    while (line[i] && is_printable(line[i]))
      i++;
  }

  return (array);
}
static int		read_polygon_components(
          t_obj_data *data,
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

    ctokens = split_polygon_components(tokens[i]);

    if (!read_vertex(data, (const char **)ctokens, is_texture_set, new_polygon))
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
int				read_polygon(t_obj_data *data, const char **tokens)
{
	t_polygon	new_polygon;

  if (!read_polygon_components(data, tokens, &new_polygon))
		return (-1);

  ft_lstadd(data->polygons,
		ft_lstnew(&new_polygon, sizeof(t_polygon)));

  return (0);
}
