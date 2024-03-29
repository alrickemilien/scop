#include "object_loader.h"

static const t_type_match	g_type_matches[9] = {
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
		&read_uv,
	},
	{
		NORMAL_TOKEN,
		&read_normal_vector,
	},
	{
		FACE_TOKEN,
		&read_face,
	},
	{
		NAME_TOKEN,
		&read_name,
	},
	{
		USEMTL_TOKEN,
		&read_usemtl,
	},
	{
		MTLLIB_TOKEN,
		&read_mtllib,
	},
	{
		SMOOTH_SHADING_AROUND_POLYGON_TOKEN,
		&read_smooth_shading,
	},
};

static t_parse_function			get_parse_func(
		const t_token *token)
{
	size_t	i;

	i = 0;
	while (i * sizeof(t_type_match) < sizeof(g_type_matches))
	{
		if (!strncmp(g_type_matches[i].token, token->cursor, token->size))
			return (g_type_matches[i].f);
		i++;
	}
	return (NULL);
}

/*
** Split each token of the line
** Get the function according to the first token
*/

int								read_object_file_line(
		t_mesh *data,
		const char *line)
{
	t_token				*tokens;
	t_parse_function	parse_function;

	if (NULL == (tokens = split_into_tokens(line, NULL)))
		return (0);
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
