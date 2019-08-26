/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_object_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:11:45 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:11:48 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "object_loader.h"

/*
** Fill all vertices componenets
** Done at the end after all vertices has been read
*/

static int	fill_vertices_data(t_mesh *data, t_list *vertices)
{
	int		error;

	error = 0;
	while (vertices)
	{
		if (fill_vertex_position(data, vertices->content) < 0)
			error = -1;
		if (fill_vertex_uv(data, vertices->content) < 0)
			error = -1;
		if (fill_vertex_normal(data, vertices->content) < 0)
			error = -1;
		vertices = vertices->next;
	}
	return (error);
}

/*
** @TODO Correct this function
** The computed normal is wrong here
*/

static void	fill_face_normal(t_polygon *polygon)
{
	t_vec3 v1;
	t_vec3 v2;

	v1 = *(t_vec3*)polygon->vertices->content;
	v2 = *(t_vec3*)polygon->vertices->next->content;
	v1 = cross_vec3(v1, v2);
	polygon->normal = v1;
}

/*
** Fill all faces vertices componenets
** Done at the end after all vertices has been read
*/

static int	fill_poylgons_vertices_data(t_mesh *data, t_list *polygons)
{
	t_polygon	*p;
	int			error;

	error = 0;
	while (polygons)
	{
		p = (t_polygon*)polygons->content;
		if (fill_vertices_data(data, p->vertices) == -1)
			error = -1;
		fill_face_normal(p);
		polygons = polygons->next;
	}
	return (error);
}

static void	reorder_lists(t_mesh *data)
{
	ft_lstreverse(&data->uvs);
	ft_lstreverse(&data->normals);
	ft_lstreverse(&data->positions);
	ft_lstreverse(&data->vertices);
	ft_lstreverse(&data->polygons);
	if (data->usemtl != NULL)
		((t_usemtl*)data->usemtl->content)->end = data->faces_count - 1;
	fill_poylgons_vertices_data(data, data->polygons);
	fill_vertices_data(data, data->vertices);
}

int			load_object_file(t_mesh *data, const char *file_path)
{
	FILE	*fp;
	char	line[LOADER_LINE_BUFF_SIZE];
	size_t	g_current_line;

	g_current_line = 0;
	memset(data, 0, sizeof(t_mesh));
	data->path = strdup(file_path);
	if (!(fp = fopen(file_path, "r")))
		return (-1);
	while (fgets(line, BUFF_SIZE, fp) != NULL && ++g_current_line)
	{
		if (line[0] == '\n')
			continue ;
		if (read_object_file_line(data, line) < 0)
		{
			fclose(fp);
			return (-1);
		}
	}
	fclose(fp);
	reorder_lists(data);
	printf("%ld polygons have been loaded.\n", ft_lstlen(data->polygons));
	return (0);
}
