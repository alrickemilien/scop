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

    delete_matrix(env->model_matrix);

    env->scale += 0.1;

	env->model_matrix = scale_matrix4x4(env->scale);
}

void scale_down(t_software_environ *env, GLFWwindow* window)
{
	(void)window;

    delete_matrix(env->model_matrix);

    env->scale -= 0.1;

	env->model_matrix = scale_matrix4x4(env->scale);
}