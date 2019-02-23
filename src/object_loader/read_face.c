#include <string.h>
#include "object_loading.h"

/*
** Face elements
**
** - Vertex indices
** A valid vertex index matches the corresponding vertex elements of a previously defined vertex list.
** If an index is positive then it refers to the offset in that vertex list, starting at 1.
**
** !WARNING If an index is negative then it relatively refers to the end of the vertex list, -1 referring to the last element.
**
** Each face can contain three or more vertices.
** f v1 v2 v3 ....
**
** - Vertex texture coordinate indices
** Optionally, texture coordinate indices can be used to specify texture coordinates when defining a face.
** To add a texture coordinate index to a vertex index when defining a face, one must put a slash immediately after the vertex index and then put the texture coordinate index.
** No spaces are permitted before or after the slash.
** A valid texture coordinate index starts from 1 and matches the corresponding element in the previously defined list of texture coordinates.
** Each face can contain three or more elements.
**
** f v1/vt1 v2/vt2 v3/vt3 ...
**
** - Vertex normal indices without texture coordinate indices
** As texture coordinates are optional, one can define geometry without them, but one must put two slashes after the vertex index before putting the normal index.
**
** f v1//vn1 v2//vn2 v3//vn3 ...
*/

static int		read_face_components(
          t_obj_data *data,
					const t_token *tokens,
					t_polygon *new_polygon)
{
	int			i;
	bool			is_texture_set;
	t_token *ctokens;
	char *tmp;

	if (!check_tokens_number(tokens, 3))
		read_object_error("A face must declare at least three vertices.");

	// Start at 1 becase of the f at the start of f X Y Z
	i = 0;
	while (tokens[i].cursor)
	{
		is_texture_set = false;

		// When two slashes are present, it means in regular case that it is
		// a vertex normal indices without texture coordinate indices
    if (strstr(tokens[i].cursor, "//"))
			is_texture_set = true;

		tmp = strndup(tokens[i].cursor, tokens[i].size);

		// Split the token 12/888/3018
		// Into three sub tokens 12, 888, and 3018
		// Split the token without slash 12
		// Into one sub token 12
		ctokens = split_into_tokens(tmp, "/");

    if (read_vertex(data, (const t_token *)ctokens, is_texture_set, new_polygon) < 0)
		{
			free(tmp);
			free(ctokens);
			return (-1);
		}

    i++;

    free(tmp);
    free(ctokens);
	}

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

int				read_face(t_obj_data *data, const t_token *tokens)
{
	t_polygon	new_polygon;

	new_polygon.vertices = NULL;

  if (!read_face_components(data, tokens, &new_polygon))
		return (-1);

  ft_lstadd(&data->polygons,
		ft_lstnew(&new_polygon, sizeof(t_polygon)));

  return (0);
}
