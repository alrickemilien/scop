#include "scop.h"

extern t_software_environ *env;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    delete_matrix(env->projection_matrix);

	env->projection_matrix = perspective_mat4(
		90.0f,
		(GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT),
		1.0f,
		2000.0f);
}