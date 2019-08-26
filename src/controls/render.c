/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:03:03 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:03:18 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static const GLenum g_render_styles[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_LINE_STRIP_ADJACENCY,
	GL_LINES_ADJACENCY,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP_ADJACENCY,
	GL_TRIANGLES_ADJACENCY,
	GL_PATCHES,
};

void				switch_render_style(
		t_software_environ *env,
		GLFWwindow *window)
{
	size_t i;

	(void)window;
	i = 0;
	while (sizeof(GLenum) * i < sizeof(g_render_styles))
	{
		if (env->render_style == g_render_styles[i])
		{
			env->render_style =
				sizeof(GLenum) * (i + 1) < sizeof(g_render_styles) ?
				g_render_styles[i + 1] : g_render_styles[0];
			return ;
		}
		i++;
	}
}

void				render_normals(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->render_normals = !env->render_normals;
}

void				render_texture(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	if (!env->texture.is_texture_loaded)
	{
		env->is_texture_rendered = false;
		return ;
	}
	env->is_texture_rendered = !env->is_texture_rendered;
}

void				render_greyscale(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->grey_scale = !env->grey_scale;
}
