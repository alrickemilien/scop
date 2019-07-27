#include "scop.h"

static void	glew_init(void)
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	// Problem: glewInit failed, something is seriously wrong.
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

/*
** Init the system display using OpenGL library
*/

void		glfw_init(t_software_environ *env, int argc, char **argv)
{
	WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
	WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

	(void)argv;
	(void)argc;

	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
		exit_error_with_message("Failed to initialize GLFW");

	// Se the antialiasing => pixels are subdivided by X
		// glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SOFT_GLFW_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SOFT_GLFW_CONTEXT_VERSION_MINOR);

	// To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	WINDOW = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);

	if (!WINDOW)
	{
		glfwTerminate();
		exit_error_with_message("Failed to open GLFW window. Need GPU compatible with 4.0 OpenGL library");
	}

	glfwSetKeyCallback(WINDOW, key_callback);

	glfwSetWindowSizeCallback(WINDOW, window_size_callback);
	glfwSetFramebufferSizeCallback(WINDOW, window_size_callback);

	glfwMakeContextCurrent(WINDOW);
	
	printf("OpenGL %s, GLSL %s\n", 
    		glGetString(GL_VERSION),
    		glGetString(GL_SHADING_LANGUAGE_VERSION));

	glew_init();
}