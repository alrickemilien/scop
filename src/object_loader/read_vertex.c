#include "object_loader.h"

int		fill_vertex_position(t_obj_data *data, t_vertex *vertex)
{
	t_vec3		*pos;

	// Substract 1 because stored indexes is the index of obj object that do not start at 0
	pos = lst_data_at(data->positions, vertex->position_index - 1);

	if (!pos)
		return read_object_error("Invalid index for a position.");

	vertex->position = pos;

	return 0;
}

int		fill_vertex_color(t_obj_data *data, t_vertex *vertex)
{
	t_vec2		*color;

	printf("Fill vertex color\n");

	// Substract 1 because stored indexes is the index of obj object that do not start at 0
	color = lst_data_at(data->uvs, vertex->position_index - 1);

	if (!color)
		return read_object_error("Invalid index for color.");

	vertex->uv = color;

	return 0;
}

int		fill_vertex_normal(t_obj_data *data, t_vertex *vertex)
{
	t_vec3		*normal;

	printf("Fill vertex normal\n");
	
	// Substract 1 because stored indexes is the index of obj object that do not start at 0
	normal = lst_data_at(data->normals, vertex->position_index - 1);

	if (!normal)
    	return read_object_error("Invalid index for normal.");

	vertex->normal = normal;

	return 0;
}

static size_t read_index(t_obj_data *data, const t_token *tokens, size_t token_index)
{
	int			index;

		index = token_to_int(tokens, token_index);

  if (index == 0)
	{
		read_object_error("Invalid index for a position, must start at 1 or -1.");
		return (size_t)-1;
	}

	// Handle negative
  if (index < 0)
		index = ft_lstlen(data->positions) + index;

	return (size_t)index;
}

static bool is_vertex_same(const void *a, const void *b)
{
	t_vertex *va;
	t_vertex *vb;

	va = (t_vertex*)a;
	vb = (t_vertex*)b;
	
	if (va->position_index == vb->position_index)
		return true;

	return false;
}

/*
** Called from read_face
** It is not a handler function
** for a type vertex that do not exists in obj file
*/

int				read_vertex(t_obj_data *data, const t_token *tokens, t_polygon *polygon)
{
	t_vertex	new_vertex;
	size_t		tokens_number;

	memset(&new_vertex, 0, sizeof(t_vertex));

	if (!tokens->cursor[0])
		return read_object_error("A face component can't be empty.");

	// Compute tokens array length
	tokens_number = 0;
	while (tokens[tokens_number].cursor)
		tokens_number++;

	// Fill index of each components
	new_vertex.position_index = read_index(data, tokens, 0);

	if (tokens_number > 1)
		new_vertex.color_index = read_index(data, tokens, 1);

	if (tokens_number > 2)
		new_vertex.normal_index = read_index(data, tokens, 2);

	if (ft_lstindex(data->vertices, &new_vertex, &is_vertex_same) == (size_t)-1)
		ft_lstadd(&data->vertices, ft_lstnew(&new_vertex, sizeof(t_vertex)));

	ft_lstadd(&polygon->vertices, ft_lstnew(&new_vertex, sizeof(t_vertex)));
	
	return (0);
}
