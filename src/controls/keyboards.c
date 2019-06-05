#include "scop.h"

/*
** This file contains keyboard callbacks
** They have to follow this proto : void f(t_software_environ *env, GLFWwindow* window)
*/

void close_window_callback(t_software_environ *env, GLFWwindow* window)
{
	(void)env;
	glfwSetWindowShouldClose(window, 1);
}

void scale_up(t_software_environ *env, GLFWwindow* window)
{
	(void)window;

    env->scale += 0.1f;

	scale_mat4(env->model_matrix, env->scale);
}

void scale_down(t_software_environ *env, GLFWwindow* window)
{
	(void)window;

    env->scale -= 0.1f;

	scale_mat4(env->model_matrix, env->scale);
}

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

void switch_render_style(t_software_environ *env, GLFWwindow* window)
{
	size_t i;
	(void)window;

	i = 0;
	while (sizeof(GLenum) * i < sizeof(g_render_styles))
	{
		if (env->render_style == g_render_styles[i])
		{
			env->render_style = 
				sizeof(GLenum) * (i + 1) < sizeof(g_render_styles)
					? g_render_styles[i + 1]
					: g_render_styles[0];
			return;
		}

		i++;
	}
}