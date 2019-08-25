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
