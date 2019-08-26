/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:58:32 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:59:44 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

extern t_software_environ	*g_env;

static bool					g_closing = false;

/*
** Clear the environnement in memory
*/

static void					del(
		void *p, size_t s)
{
	(void)s;
	free(p);
}

static void					clear_env_memory(void)
{
	if (!g_env)
		return ;
	if (g_env->texture.is_texture_loaded)
		free(g_env->texture.data);
	if (g_env->data.name)
		free(g_env->data.name);
	if (g_env->data.path)
		free(g_env->data.path);
	if (g_env->data.mtl)
		free(g_env->data.mtl);
	if (g_env->data.positions)
		ft_lstdel(&g_env->data.positions, &del);
	if (g_env->data.uvs)
		ft_lstdel(&g_env->data.uvs, &del);
	if (g_env->data.normals)
		ft_lstdel(&g_env->data.normals, &del);
	if (g_env->data.uvs)
		ft_lstdel(&g_env->data.uvs, &del);
	if (g_env->data.vertices)
		ft_lstdel(&g_env->data.vertices, &del_vertex);
	ft_lstdel(&g_env->data.usemtl, &del_usemtl);
	ft_lstdel(&g_env->data.mtllib, &del_mtllib);
	if (g_env->data.polygons)
		ft_lstdel(&g_env->data.polygons, &del_polygon);
	free(g_env);
}

void						end_program(int code)
{
	if (g_closing)
		return ;
	g_closing = true;
	cleanup_shader_program(&g_env->object_shader_program);
	cleanup_shader_program(&g_env->internal_object_shader_program);
	glDeleteBuffers(1, &g_env->vbo);
	glDeleteBuffers(1, &g_env->plan_vbo);
	glDeleteBuffers(1, &g_env->axis_vbo);
	if (g_env->indexation_mode)
		glDeleteBuffers(1, &g_env->ebo);
	glDeleteVertexArrays(1, &g_env->vao);
	glDeleteVertexArrays(1, &g_env->plan_vao);
	glDeleteVertexArrays(1, &g_env->axis_vao);
	if (g_env->texture.is_texture_loaded)
		glDeleteTextures(1, &g_env->texture_uni);
	glfwTerminate();
	clear_env_memory();
	printf("Closed.\n");
	exit(code);
}
