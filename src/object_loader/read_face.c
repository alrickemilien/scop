#include <string.h>
#include "object_loader.h"

/*
** Split the token 12/888/3018
** Into three sub tokens 12, 888, and 3018
** Split the token without slash 12
** Into one sub token 12
*/

static int	read_polygon_vertex(
		t_mesh *data,
		t_polygon *new_polygon,
		t_token t)
{
	t_token	*ctokens;
	char	*tmp;

	tmp = strndup(t.cursor, t.size);
	ctokens = split_into_tokens(tmp, "/");
	if (read_vertex(data, (const t_token *)ctokens, new_polygon) < 0)
	{
		free(tmp);
		free(ctokens);
		return (-1);
	}
	free(tmp);
	free(ctokens);
	return (0);
}

static int	read_quadrilateral_face_component(
		t_mesh *data,
		const t_token *tokens)
{
	size_t		i;
	t_polygon	new_polygon_a;
	t_polygon	new_polygon_b;

	memset(&new_polygon_a, 0, sizeof(t_polygon));
	memset(&new_polygon_b, 0, sizeof(t_polygon));
	i = 0;
	while (tokens[i].cursor)
		if (strstr(tokens[i++].cursor, "//"))
			data->is_texture_set = true;
	if (read_polygon_vertex(data, &new_polygon_a, tokens[0]) == -1
		|| read_polygon_vertex(data, &new_polygon_a, tokens[1]) == -1
		|| read_polygon_vertex(data, &new_polygon_a, tokens[2]) == -1)
		return (-1);
	ft_lstreverse(&new_polygon_a.vertices);
	ft_lstadd(&data->polygons,
			ft_lstnew(&new_polygon_a, sizeof(t_polygon)));
	if (read_polygon_vertex(data, &new_polygon_b, tokens[2]) == -1
		|| read_polygon_vertex(data, &new_polygon_b, tokens[3]) == -1
		|| read_polygon_vertex(data, &new_polygon_b, tokens[0]) == -1)
		return (-1);
	ft_lstreverse(&new_polygon_b.vertices);
	ft_lstadd(&data->polygons,
			ft_lstnew(&new_polygon_b, sizeof(t_polygon)));
	return (0);
}

/*
** Face elements
** - Vertex indices
** A valid vertex index matches the corresponding vertex elements
** of a previously defined vertex list.
** If an index is positive then it refers
** to the offset in that vertex list, starting at 1.
** !WARNING If an index is negative then it relatively refers
** to the end of the vertex list,
** -1 referring to the last element.
** Each face can contain three or more vertices.
** f v1 v2 v3 ....
** - Vertex texture coordinate indices
** Optionally, texture coordinate indices can be used
** to specify texture coordinates when defining a face.
** To add a texture coordinate index to a vertex index when defining a face,
** one must put a slash immediately after the vertex index
** and then put the texture coordinate index.
** No spaces are permitted before or after the slash.
** A valid texture coordinate index starts from 1
** and matches the corresponding element
** in the previously defined list of texture coordinates.
** Each face can contain three or more elements.
** f v1/vt1 v2/vt2 v3/vt3 ...
** - Vertex normal indices without texture coordinate indices
** As texture coordinates are optional, one can define geometry without them,
** but one must put two slashes
** after the vertex index before putting the normal index.
** f v1//vn1 v2//vn2 v3//vn3 ...
*/

static int	read_face_components(
		t_mesh *data,
		const t_token *tokens)
{
	size_t		i;
	t_polygon	new_polygon;

	new_polygon.vertices = NULL;
	if (!check_tokens_number(tokens, 3))
		return (read_object_error("A face must declare at least 3 vertices."));
	i = 0;
	while (tokens[i].cursor)
		i++;
	if (i == 4)
		return (read_quadrilateral_face_component(data, tokens));
	i = 0;
	while (tokens[i].cursor)
	{
		if (strstr(tokens[i].cursor, "//"))
			data->is_texture_set = true;
		if (read_polygon_vertex(data, &new_polygon, tokens[i]) == -1)
			return (-1);
		i++;
	}
	ft_lstreverse(&new_polygon.vertices);
	ft_lstadd(&data->polygons,
			ft_lstnew(&new_polygon, sizeof(t_polygon)));
	return (0);
}

/*
** Read following polygon schema in object file :
** f 16 2 3 17
** or
** f 1381//17765 9428//17765 1382//17765
** f 1381//17765 9428//17765 1382//17765
** ...
*/

int			read_face(t_mesh *data, const t_token *tokens)
{
	data->faces_count++;
	if (read_face_components(data, tokens) < 0)
		return (-1);
	return (0);
}
