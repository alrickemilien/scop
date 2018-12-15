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
		&read_normal_vector,
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

static t_parse_function get_parse_func(const t_token *token)
{
	size_t		i;

	i = 0;
	while (g_type_matches[i].token && g_type_matches[i].f)
	{
		if (!strncmp(g_type_matches[i].token, token->cursor, token->size))
			return (g_type_matches[i].f);

    i++;
	}

  return (NULL);
}

int			read_object_file_line(t_obj_data *data, const char *line)
{
	t_token	*tokens;
	t_parse_function parse_function;

  // Spli each token of the line
	if (NULL == (tokens = split_into_tokens(line, NULL)))
		return (0);


  // Get the function according to the first token
  parse_function = get_parse_func(tokens);

  if (!parse_function)
	{
		puts(tokens[0].cursor);
		free(tokens);

    return (-1);
	}

  (*parse_function)(data, (const t_token *)(tokens + 1));

	free(tokens);

	return (0);
}
