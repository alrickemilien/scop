#include "object_loader.h"

/*
** Substract 1 because stored indexes
** is the index of obj object that do not start at 0
*/

int				fill_vertex_position(t_mesh *data, t_vertex *vertex)
{
	t_vec3		*pos;

	pos = lst_data_at(data->positions, vertex->position_index - 1);
	if (!pos)
		return (read_object_error("Invalid index for a position."));
	vertex->position = pos;
	return (0);
}

/*
** Substract 1 because stored indexes
** is the index of obj object that do not start at 0
*/

int				fill_vertex_uv(t_mesh *data, t_vertex *vertex)
{
	t_vec2		*uv;

	uv = lst_data_at(data->uvs, vertex->uv_index - 1);
	if (!uv)
		return (read_object_error("Invalid index for uv."));
	vertex->uv = uv;
	return (0);
}

int				fill_vertex_normal(t_mesh *data, t_vertex *vertex)
{
	t_vec3		*normal;

	normal = lst_data_at(data->normals, vertex->normal_index - 1);
	if (!normal)
		return (read_object_error("Invalid index for normal."));
	vertex->normal = normal;
	return (0);
}

static size_t	read_index(
		t_mesh *data,
		const t_token *tokens,
		size_t token_index,
		size_t max)
{
	int	index;

	(void)data;
	index = token_to_int(tokens, token_index);
	if (index == 0)
	{
		read_object_error(
			"Invalid index for a position, must start at 1 or -1.");
		return ((size_t)-1);
	}
	if (index < 0)
		index = max + index;
	return ((size_t)index);
}

/*
** Called from read_face
** It is not a handler function
** for a type vertex that do not exists in obj file
*/

int				read_vertex(
		t_mesh *data,
		const t_token *tokens,
		t_polygon *polygon)
{
	t_vertex	new_vertex;
	size_t		tokens_number;

	memset(&new_vertex, 0, sizeof(t_vertex));
	if (!tokens->cursor[0] || strcmp(tokens->cursor, "//") == 0)
		return (read_object_error("A face component can't be empty."));
	tokens_number = 0;
	while (tokens[tokens_number].cursor)
		tokens_number++;
	if (strstr(tokens->cursor, "//") && tokens->cursor[0] == '/')
		return (read_object_error("A face component can't be empty."));
	new_vertex.position_index = read_index(
			data, tokens, 0, ft_lstlen(data->positions));
	if (tokens_number > 1 && !strstr(tokens->cursor, "//"))
		new_vertex.uv_index = read_index(data, tokens, 1, ft_lstlen(data->uvs));
	if (tokens_number > 2)
		new_vertex.normal_index = read_index(
				data, tokens, 2, ft_lstlen(data->normals));
	else if (tokens_number > 1 && strstr(tokens->cursor, "//"))
		new_vertex.normal_index = read_index(
				data, tokens, 1, ft_lstlen(data->normals));
	if (ft_lstindex(data->vertices, &new_vertex, &is_vertex_same) == (size_t)-1)
		ft_lstadd(&data->vertices, ft_lstnew(&new_vertex, sizeof(t_vertex)));
	ft_lstadd(&polygon->vertices, ft_lstnew(&new_vertex, sizeof(t_vertex)));
	return (0);
}
