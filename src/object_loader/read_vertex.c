#include "object_loading.h"

static void		fill_vertex_position(const char **tokens, t_vertex *vertex)
{
	int			index;
	t_lst		*positions;
	t_vec3		*pos;

	index = token_to_int(tokens, 0);

  positions = g_current_data->positions;

  pos = lst_data_at(positions, index);

  if (pos)
	{
		vertex->position.x = pos->x;
		vertex->position.y = pos->y;
		vertex->position.z = pos->z;
	}
	else if (index >= 0 && lst_get_size(positions) > (size_t)index)
	{
		vertex->position.x = FLT_MAX;
		vertex->position.y = FLT_MAX;
		vertex->position.z = FLT_MAX;
	}
	else
		read_object_error("Invalid index for a position.");
}

static void		fill_vertex_color(const char **tokens, t_vertex *vertex, int nt)
{
	int			i;
	t_lst		*colors;
	t_vec2		*color;

	colors = g_current_data->uvs;
	i = DEFAULT_CODE;

  if (!nt)
		i = token_to_int(tokens, 1);

  color = lst_data_at(colors, i);

  if (color)
	{
		vertex->uv.x = color->x;
		vertex->uv.y = color->y;
	}

  else if (i == DEFAULT_CODE || (i >= 0 && lst_get_size(colors) > (size_t)i))
	{
		vertex->uv.x = FLT_MAX;
		vertex->uv.y = FLT_MAX;
	}

  else {
    read_object_error("Invalid index for color.");
  }
}

static void		fill_vertex_normal(const char **tokens, t_vertex *vertx, int nt)
{
	int			i;
	t_lst		*normals;
	t_vec3		*normal;

	normals = g_current_data->normals;

  i = token_to_int(tokens, 2);

  if (nt)
		i = token_to_int(tokens, 1);

  normal = lst_data_at(normals, i);

  if (normal)
	{
		vertx->normal.x = normal->x;
		vertx->normal.y = normal->y;
		vertx->normal.z = normal->z;
	}

	else if (i == DEFAULT_CODE || (i >= 0 && lst_get_size(normals) > (size_t)i))
	{
		vertx->normal.x = FLT_MAX;
		vertx->normal.y = FLT_MAX;
		vertx->normal.z = FLT_MAX;
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

int				read_vertex(const char **tokens, bool is_texture_set, t_lst *vertices)
{
	t_vertex	*new_vertex;

	new_vertex = NULL;
	if (!tokens[0])
		read_object_error("A face component can't be empty.");
	else if (!(new_vertex = malloc(sizeof(t_vertex))))
		return (-1);

  fill_vertex_position(tokens, new_vertex);

  fill_vertex_color(tokens, new_vertex, is_texture_set);

  fill_vertex_normal(tokens, new_vertex, is_texture_set);

  lst_push_back(vertices, new_vertex);

  return (0);
}
