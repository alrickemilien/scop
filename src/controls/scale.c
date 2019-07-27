#include "scop.h"

void	scale_up(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;

	env->scale += 0.1f;
}

void	scale_down(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;

	env->scale -= 0.1f;
}