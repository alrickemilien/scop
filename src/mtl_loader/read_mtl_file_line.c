#include "material_template_library_loader.h"

static const t_type_match	g_type_matches[9] = {
	{
		COMMENT_TOKEN,
		&read_mtl_comment,
	},
	{
		NEWMTL_TOKEN,
		&read_new_mtl,
	},
	// {
	// 	AMBIENT_COLOR_TOKEN,
	// 	&read_ambient_color,
	// },
	// {
	// 	DIFFUSE_COLOR_TOKEN,
	// 	&read_diffuse_color,
	// },
	// {
	// 	SPECULAR_COLOR_TOKEN,
	// 	&read_specular_color,
	// },
	// {
	// 	SPECULAR_COLOR_EXPONENT_TOKEN,
	// 	&read_specular_color_exponent,
	// },
	// {
	// 	DISSOLVED_TOKEN,
	// 	&read_dissolved,
	// },
	// {
	// 	TRANSPARENCY_TOKEN,
	// 	&read_transparency,
	// },
	// {
	// 	ILLUMINATION_TOKEN,
	// 	&read_illumination,
	// },
};

static t_parse_function get_parse_func(const t_token *token)
{
	size_t		i;

	i = 0;
	while (i * sizeof(t_type_match) < sizeof(g_type_matches))
	{
		if (!strncmp(g_type_matches[i].token, token->cursor, token->size))
			return (g_type_matches[i].f);

		i++;
	}

  return (NULL);
}

int						read_mtl_file_line(
	t_mtl_list data,
	const char *line)
{
	t_token				*tokens;
	t_parse_function	parse_function;

	printf("line : %s\n", line);

	// Split each token of the line
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
