#include "object_loader.h"

static void		fill_vertex_position(t_obj_data *data, const t_token *tokens, t_vertex *vertex)
{
	int			index;
	t_vec3		*pos;

	index = token_to_int(tokens, 0) - 1;

	// @TODO need to handle negative
  if (index < 0)
	 read_object_error("A face index can't be negative.");

  pos = lst_data_at(data->positions, index);


  if (pos)
	{
		vertex->position.x = pos->x;
		vertex->position.y = pos->y;
		vertex->position.z = pos->z;
	}
	else if (index >= 0 && ft_lstlen(data->positions) > (size_t)index)
	{
		vertex->position.x = 0xFFFFFF;
		vertex->position.y = 0xFFFFFF;
		vertex->position.z = 0xFFFFFF;
	}
	else
		read_object_error("Invalid index for a position.");
}

static void		fill_vertex_color(t_obj_data *data, const t_token *tokens, t_vertex *vertex, int is_texture_set)
{
	int			i;
	t_list		*colors;
	t_vec2		*color;

	colors = data->uvs;
	i = DEFAULT_CODE;

	printf("Fill vertex color\n");

  if (!is_texture_set)
		i = token_to_int(tokens, 1);

		// @TODO need to handle negative


  color = lst_data_at(colors, i);

  if (color)
	{
		vertex->uv.x = color->x;
		vertex->uv.y = color->y;
	}

  else if (i == DEFAULT_CODE || (i >= 0 && ft_lstlen(colors) > (size_t)i))
	{
		vertex->uv.x = 0xFFFFFF;
		vertex->uv.y = 0xFFFFFF;
	}

  else {
    read_object_error("Invalid index for color.");
  }
}

static void		fill_vertex_normal(t_obj_data *data, const t_token *tokens, t_vertex *vertx, int nt)
{
	int			i;
	t_list		*normals;
	t_vec3		*normal;

	normals = data->normals;

	// @TODO need to handle negative
	i = token_to_int(tokens, 2) - 1;

 	if (i < 0)
	 read_object_error("A face index can't be negative.");

  if (nt)
		i = token_to_int(tokens, 1);

  normal = lst_data_at(normals, i);

  if (normal)
	{
		vertx->normal.x = normal->x;
		vertx->normal.y = normal->y;
		vertx->normal.z = normal->z;
	}

	else if (i == DEFAULT_CODE || (i >= 0 && ft_lstlen(normals) > (size_t)i))
	{
		vertx->normal.x = 0xFFFFFF;
		vertx->normal.y = 0xFFFFFF;
		vertx->normal.z = 0xFFFFFF;
	}

	else {
    read_object_error("Invalid index for normal.");
  }
}

/*
** Called from read_polygon
** It is not a handler function
** for a type vertex that do not exists in obj file
*/

int				read_vertex(t_obj_data *data, const t_token *tokens, bool is_texture_set, t_polygon *polygon)
{
	t_vertex	new_vertex;
	size_t	tokens_number;

	if (!tokens->cursor[0])
		read_object_error("A face component can't be empty.");

  // Compute tokens array length
	tokens_number = 0;
	while (tokens[tokens_number].cursor)
		tokens_number++;

  fill_vertex_position(data, tokens, &new_vertex);

	printf("tokens_number : %ld\n", tokens_number);
	printf("tokens[0].cursor : %s\n", tokens[0].cursor);
	if (tokens[0].cursor) printf("tokens[1].cursor : %s\n", tokens[1].cursor);
	if (tokens[1].cursor) printf("tokens[2].cursor : %s\n", tokens[2].cursor);

	if (tokens_number > 1)
  	fill_vertex_color(data, tokens, &new_vertex, is_texture_set);

	if (tokens_number > 1)
  	fill_vertex_normal(data, tokens, &new_vertex, is_texture_set);

  ft_lstadd(&polygon->vertices, ft_lstnew(&new_vertex, sizeof(t_vertex)));

  return (0);
}
