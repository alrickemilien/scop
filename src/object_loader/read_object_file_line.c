#include "object_loading.h"

static const t_type_match	g_type_matches[] = {
	{
		COMMENT_TOKEN,
		&read_comment,
	},
	{
		POSITION_TOKEN,
		&read_position,
	},
	{
		COLOR_TOKEN,
		&read_color,
	},
	{
		NORMAL_TOKEN,
		&read_normal,
	},
	{
		POLYGON_TOKEN,
		&read_polygon,
	},
	{
		NULL,
		NULL
	}
};

static t_parse_function get_parse_func(const char *input)
{
	size_t		i;

	i = 0;
	while (g_type_matches[i].token && g_type_matches[i].f)
	{
		if (!strcmp(g_type_matches[i].token, input))
			return (g_type_matches[i].f);

    i++;
	}

  return (NULL);
}

static char **split_tokens(const char *line) {
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
    while (line[i] && !is_printable(line[i]))
      i++;

		memcpy(array[i], line + i, sizeof(char*));

    while (line[i] && is_printable(line[i]))
      i++;
  }

  return (array);
}

int			read_object_file_line(t_obj_data *data, const char *line)
{
	char	**tokens;
	t_parse_function parse_function;

  // Spli each token of the line
	if (NULL == (tokens = split_tokens(line)))
		return (0);

  // Get the function according to the first token
  parse_function = get_parse_func(tokens[0]);

  if (!parse_function)
	{
		puts(tokens[0]);
		free(tokens);

    return (-1);
	}

  (*parse_function)(data, (const char **)(tokens + 1));

	free(tokens);

	return (0);
}
