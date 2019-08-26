/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_indexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:34:19 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:42:16 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static const size_t	g_vertex_size = sizeof(t_vec3) * 3;
static const t_vec3	g_color = {1.0f, 1.0f, 1.0f};

/*
** Provides VBO indexing style functions
** may be slower to setup but same perf on render
** and more accurate on render
*/

static void			vertex_list_to_vbo(
		t_software_environ *env,
		GLfloat *buffer)
{
	size_t		i;
	t_list		*x;
	t_vertex	*vertex;
	t_vec3		normal;

	memset(buffer, 0, g_vertex_size * ft_lstlen(env->data.vertices));
	i = 0;
	x = env->data.vertices;
	while (x)
	{
		vertex = (t_vertex*)x->content;
		memcpy(buffer + i * g_vertex_size,
			vertex->position, sizeof(t_vec3));
		memcpy(buffer + i * g_vertex_size + sizeof(t_vec3),
			vertex->color == NULL ? &g_color : vertex->color, sizeof(t_vec3));
		if (vertex->normal == NULL)
			compute_vertex_normal(&env->data, vertex, &normal);
		memcpy(buffer + i * g_vertex_size + 2 * sizeof(t_vec3),
			vertex->normal == NULL ? &normal : vertex->normal, sizeof(t_vec3));
		i++;
		x = x->next;
	}
	glGenBuffers(1, &env->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, i * g_vertex_size, buffer, GL_STATIC_DRAW);
}

/*
** This is the size of memory of polygon vertex
** It is composed of many vertices
** Each vertice is composed of position, color uv and normal
*/

static void			load_polygon_into_index_buffer(
		t_software_environ *env,
		t_polygon *polygon,
		void *index_buffer)
{
	t_list		*x;
	size_t		i;
	GLuint		index;

	i = 0;
	x = polygon->vertices;
	while (x)
	{
		index = (GLuint)ft_lstindex(env->data.vertices,
				x->content, &is_vertex_same);
		memcpy((uint8_t*)index_buffer + i * sizeof(GLuint),
				&index, sizeof(GLuint));
		i++;
		x = x->next;
	}
}

/*
** Convert a list into a ebo ( GL vertex buffer object )
*/

static int			vertex_list_to_ebo(
		t_software_environ *env)
{
	size_t		i;
	size_t		j;
	t_list		*x;
	GLuint		*ib;
	size_t		poly_length;

	if (!(ib = (GLuint*)malloc(env->data.vertex_count * sizeof(GLuint))))
		return (-1);
	memset(ib, 0, env->data.vertex_count * sizeof(GLuint));
	i = 0;
	j = 0;
	x = env->data.polygons;
	while (x)
	{
		poly_length = ft_lstlen(((t_polygon*)x->content)->vertices);
		load_polygon_into_index_buffer(env, x->content, ((uint8_t*)ib + i));
		i += sizeof(GLuint) * poly_length;
		j++;
		x = x->next;
	}
	glGenBuffers(1, &env->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i, ib, GL_STATIC_DRAW);
	free(ib);
	return (0);
}

static int			vertex_list_to_vao(
		t_software_environ *env)
{
	GLfloat		*buffer;

	glGenVertexArrays(1, &env->vao);
	check_gl_error();
	glBindVertexArray(env->vao);
	if (!(buffer = (GLfloat*)malloc(
		g_vertex_size * ft_lstlen(env->data.vertices))))
		return (-1);
	vertex_list_to_vbo(env, buffer);
	free(buffer);
	if (vertex_list_to_ebo(env) < 0)
		return (-1);
	return (0);
}

int					gl_indexing(
		t_software_environ *env)
{
	if (glGenVertexArrays == NULL)
		end_program(-1);
	if (glBindVertexArray == NULL)
		end_program(-1);
	if (vertex_list_to_vao(env) < 0 || set_attribute(
				env->object_shader_program.id, "position", g_vertex_size) < 0)
		return (-1);
	if (set_attribute(
				env->object_shader_program.id, "color", g_vertex_size) < 0)
		return (-1);
	if (set_attribute(
				env->object_shader_program.id, "normal", g_vertex_size) < 0)
		return (-1);
	if (plan_to_vbo(env) < 0 || set_attribute(
				env->internal_object_shader_program.id,
				"position", sizeof(t_vec3)) < 0)
		return (-1);
	if (axis_to_vbo(env) < 0 || set_attribute(
				env->axis_shader_program.id, "position", sizeof(t_vec3)) < 0)
		return (-1);
	return (0);
}
