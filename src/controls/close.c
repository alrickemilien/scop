#include "scop.h"

void	close_window_callback(t_software_environ *env, GLFWwindow *window)
{
	(void) env;
	glfwSetWindowShouldClose(window, 1);
}