/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_buffering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:32:11 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:45:43 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static const size_t	g_vertex_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);
static const t_vec3	g_color = {1.0f, 1.0f, 1.0f};
static const t_vec2	g_uvs[3] = {
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{0.5f, 1.0f},
};

/*
** This is the size of memory of polygon vertex
** It is composed of many vertices
** Each vertice is composed of position, color uv and normal
*/

static void	load_polygon_into_data(
		t_software_environ *env,
		t_polygon *polygon,
		void *buffer)
{
	t_list		*x;
	size_t		i;
	t_vertex	*vertex;
	t_vec3		normal;

	i = 0;
	x = polygon->vertices;
	while (x)
	{
		vertex = (t_vertex *)x->content;
		memcpy((uint8_t*)buffer + i * g_vertex_size,
			vertex->position, sizeof(t_vec3));
		memcpy((uint8_t*)buffer + i * g_vertex_size + sizeof(t_vec3),
			&g_color, sizeof(t_vec3));
		if (vertex->normal == NULL)
			compute_vertex_normal(&env->data, vertex, &normal);
		memcpy((uint8_t*)buffer + i * g_vertex_size + 2 * sizeof(t_vec3),
			vertex->normal == NULL ? &normal : vertex->normal, sizeof(t_vec3));
		memcpy((uint8_t*)buffer + i * g_vertex_size + 3 * sizeof(t_vec3),
			vertex->uv == NULL ? &g_uvs[i % 3] : vertex->uv, sizeof(t_vec2));
		i++;
		x = x->next;
	}
}

/*
** Convert a list into a vbo ( GL vertex buffer object )
*/

static int	vertex_list_to_vbo(t_software_environ *env)
{
	size_t	i;
	t_list	*x;
	GLfloat	*buffer;
	size_t	poly_length;

	if (!(buffer = (GLfloat*)malloc(g_vertex_size * env->data.vertex_count)))
		return (-1);
	memset(buffer, 0, g_vertex_size * env->data.vertex_count);
	i = 0;
	x = env->data.polygons;
	while (x)
	{
		poly_length = ft_lstlen(((t_polygon*)x->content)->vertices);
		load_polygon_into_data(env, x->content, (GLfloat*)((char*)buffer + i));
		i += g_vertex_size * poly_length;
		x = x->next;
	}
	glGenVertexArrays(1, &env->vao);
	glBindVertexArray(env->vao);
	glGenBuffers(1, &env->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, i, buffer, GL_STATIC_DRAW);
	free(buffer);
	return (0);
}

int			plan_to_vbo(t_software_environ *env)
{
	t_vec3	v;
	GLfloat	*plan_buffer;

	v = (t_vec3){0.f, -3.f, 0.f};
	glGenVertexArrays(1, &env->plan_vao);
	check_gl_error();
	glBindVertexArray(env->plan_vao);
	if (!(plan_buffer = (GLfloat*)malloc(sizeof(t_vec3))))
		return (-1);
	memcpy((uint8_t*)plan_buffer, &v, sizeof(t_vec3));
	glGenBuffers(1, &env->plan_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->plan_vbo);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(t_vec3), plan_buffer, GL_STATIC_DRAW);
	free(plan_buffer);
	return (0);
}

int			axis_to_vbo(t_software_environ *env)
{
	t_vec3	v;
	GLfloat	*axis_buffer;

	v = (t_vec3){0.f, 0.f, 0.f};
	glGenVertexArrays(1, &env->axis_vao);
	check_gl_error();
	glBindVertexArray(env->axis_vao);
	if (!(axis_buffer = (GLfloat*)malloc(sizeof(t_vec3))))
		return (-1);
	memcpy((uint8_t*)axis_buffer, &v, sizeof(t_vec3));
	glGenBuffers(1, &env->axis_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->axis_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3), axis_buffer, GL_STATIC_DRAW);
	free(axis_buffer);
	return (0);
}

int			gl_buffering(t_software_environ *env)
{
	if (vertex_list_to_vbo(env) < 0)
		return (-1);
	if (set_attribute(
				env->object_shader_program.id, "position", g_vertex_size) < 0)
		return (-1);
	if (set_attribute(
				env->object_shader_program.id, "color", g_vertex_size) < 0)
		return (-1);
	if (set_attribute(
				env->object_shader_program.id, "normal", g_vertex_size) < 0)
		return (-1);
	if (set_attribute(
				env->object_shader_program.id, "uv", g_vertex_size) < 0)
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
