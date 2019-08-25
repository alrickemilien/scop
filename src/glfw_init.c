#include "scop.h"

static void	glew_init(void)
{
	GLenum err;

	err = glewInit();
	glewExperimental = GL_TRUE;
	if (err != GLEW_OK)
	{
		fprintf(stderr, "glewInit failed, aborting. Code %d.\n", err);
		exit(err);
	}
}

static void	glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s (%d)\n", description, error);
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

static void	glfw_init_hint(void)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SOFT_GLFW_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SOFT_GLFW_CONTEXT_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/*
** Init the system display using OpenGL library
** To make MacOS happy; should not be needed
**	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
**	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
*/

void		glfw_init(t_software_environ *env, int argc, char **argv)
{
	env->window_width = DEFAULT_WINDOW_WIDTH;
	env->window_height = DEFAULT_WINDOW_HEIGHT;
	(void)argv;
	(void)argc;
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		exit_error_with_message("Failed to initialize GLFW");
	glfw_init_hint();
	env->window = glfwCreateWindow(
		env->window_width, env->window_height,
		WINDOW_NAME, NULL, NULL);
	if (!env->window)
	{
		glfwTerminate();
		exit_error_with_message(
			"Need GPU compatible with 4.0 OpenGL library");
	}
	glfwSetKeyCallback(env->window, key_callback);
	glfwSetWindowSizeCallback(env->window, window_size_callback);
	glfwSetFramebufferSizeCallback(env->window, window_size_callback);
	glfwMakeContextCurrent(env->window);
	printf("OpenGL %s, GLSL %s\n",
			glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));
	glew_init();
}
