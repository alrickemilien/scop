#include "scop.h"

static void	load_polygon_into_buffer(float *buffer, t_polygon const *polygon)
{
	t_list		*iter;
	size_t		i;
	t_vertex	*vertex;

	i = 0;
	iter = polygon->vertices;
	while (iter)
	{
		vertex = (t_vertex*)iter->content;

		memcpy(buffer + i * 11, &vertex->position, sizeof(t_vec3));
		memcpy(buffer + i * 11 + 3, &vertex->color, sizeof(t_vec3));
		memcpy(buffer + i * 11 + 6, &vertex->uv, sizeof(t_vec2));
		memcpy(buffer + i * 11 + 8, &vertex->normal, sizeof(t_vec3));

		i++;
		iter = iter->next;
	}
}

void		build_vertex_buffer(t_software_environ *env)
{
	size_t		i;
	t_list		*iter;
	float			*buffer_data;
	size_t		buffer_length;

	buffer_length = (3 + 3 + 2 + 3) * env->data.vertex_count;

	buffer_data = (float*)calloc(buffer_length, sizeof(float));

	iter = env->data.polygons;
	i = 0;
	while (iter)
	{
		load_polygon_into_buffer(buffer_data + i * 11, (t_polygon*)iter->content);
		i += 3;
		iter = iter->next;
	}

	glGenBuffers(1, &env->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);

	glBufferData(GL_ARRAY_BUFFER, buffer_length * sizeof(float), buffer_data,
		GL_STATIC_DRAW);
}
