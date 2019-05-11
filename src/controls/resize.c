#include "scop.h"

extern t_software_environ *env;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    env->window_width = width;
    env->window_height = height;

    delete_matrix(env->projection_matrix);

    env->projection_matrix = perspective_mat4(
	    90.0f,
	    (GLfloat)env->window_width / (GLfloat)env->window_height,
	    1.0f,
	    2000.0f);
}