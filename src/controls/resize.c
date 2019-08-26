/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:01:58 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:02:03 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

extern t_software_environ	*g_env;

void						window_size_callback(
		GLFWwindow *window,
		int width,
		int height)
{
	(void)window;
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	g_env->projection_matrix = perspective_mat4(
			90.0f,
			(GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT),
			1.0f,
			2000.0f);
}
