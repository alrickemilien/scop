#include "scop.h"

void    unlock_z_axis(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;
	env->z_axis = 0;
}

void    unlock_y_axis(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;
	env->y_axis = 0;
}

void    unlock_x_axis(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;
	env->x_axis = 0;
}
