#include "scop.h"

void    reduce_ambient_lighting(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;

	env->ambient_lighting -= 0.1f;

	if (env->ambient_lighting < 0.0f)
		env->ambient_lighting = 0.0f;
}

void    increase_ambient_lighting(
    t_software_environ *env,
    GLFWwindow *window)
{
	(void) window;

	env->ambient_lighting += 0.1f;

	if (env->ambient_lighting > 1.0f)
		env->ambient_lighting = 1.0f;
}