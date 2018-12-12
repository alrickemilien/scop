#include "object_loading.h"

typedef int	(*t_parse_function)(const char **);

static const t_type_match	g_type_matches[] = {
	{
		COMMENT_TOKEN,
		&parse_comment,
	},
	{
		POSITION_TOKEN,
		&parse_position,
	},
	{
		COLOR_TOKEN,
		&parse_color,
	},
	{
		NORMAL_TOKEN,
		&parse_normal,
	},
	{
		POLYGON_TOKEN,
		&parse_polygon,
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

static inline bool is_printable(char c)
{
  if (c >= 1 && c <= 32)
    return (false);
  return (true);
}

static char **split_tokens(const char *line) {
  size_t i;
  char   *array;

  i = 0
  while (line[i] && !is_printable(line[i]))
    i++;

  if (NULL == (array = malloc(sizeof(char*) * (i + 1))))
    return (NULL);

  array[i] = 0;

  i = 0
  while(line[i]) {
    while (line[i] && !is_printable(line[i]))
      i++;

    array[i] = line + i;

    while (line[i] && is_printable(line[i]))
      i++;
  }

  return (array);
}

int			read_object_file_line(char *line)
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

  (*parse_function)((const char **)(tokens + 1));

	free(tokens);

	return (0);
}
