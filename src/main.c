#include "scop.h"

#ifdef __APPLE__
void glew_init(void) {
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	// Problem: glewInit failed, something is seriously wrong.
	if (err != GLEW_OK)
	{
		fprintf(stderr, "glewInit failed, aborting. Code %d.\n", err);
		exit(err);
	}
}
#endif

// Close OpenGL window and terminate GLFW
void	end_program()
{
	printf("Closing app ...\n");
	glfwTerminate();
	exit(0);
}

/*
*/
void run(t_software_environ *env)
{
	GLuint program_id;

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	program_id = load_shaders(env);

	glUseProgram(program_id);

	prepare(env);

	// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(WINDOW, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WINDOW) == 0)
	{
		// // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render(env);

		// // Swap buffers
		glfwSwapBuffers(WINDOW);
		glfwPollEvents();
	}

	end_program();
}

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s (%d)\n", description, error);
}

/*
** Initialize the system with the provided resources
** - Register the current
** - Find the shader folder and register the path
** - Read the resources into the object folder
** When all ok, start the application
*/

static int init_system_resources(t_software_environ *env, int argc, char **argv)
{
	if (argc != 2)
		exit_error_with_message("Input file missing.");

	if (getcwd(env->cwd, sizeof(env->cwd)) == NULL)
		exit_error_with_message("An error occured when oading the pwd path of the program.");

	// Load provided object file
	if (load_object_file(&env->data, argv[1]) < 0)
		return (-1);

	count_vertices(&env->data);

	// All OK, start applicaton
	return (0);
}

/*
** Init the system display using OpenGL library
*/

void init(t_software_environ *env, int argc, char **argv)
{
	WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
	WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

	(void)argv;
	(void)argc;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit_error_with_message("Failed to initialize GLFW");

	glfwWindowHint(GLFW_SAMPLES, 4);
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
	};

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(WINDOW, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetKeyCallback(WINDOW, key_callback);

	glfwMakeContextCurrent(WINDOW);

#ifdef __APPLE__
	glew_init();
#endif
}

int main(int argc, char **argv)
{
	t_software_environ env;

	// Could not continue if the system ressources are fully and successfully loaded
	if (init_system_resources(&env, argc, argv) < 0)
		return (-1);

	init(&env, argc, argv);

	run(&env);

	return 0;
}
