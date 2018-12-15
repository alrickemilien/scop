#include "scop.h"

#ifdef __APPLE__
void glew_init(void) {
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed, aborting. Code %d.\n", err);
		exit(err);
	}
}
#endif

/*
*/
void run(t_software_environ *env)
{
	GLuint program_id;

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	program_id = load_shaders();

	glUseProgram(program_id);

	prepare();

	// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(WINDOW, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WINDOW) == 0)
	{
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render();

		// Swap buffers
		glfwSwapBuffers(WINDOW);
		glfwPollEvents();
	}

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void	end_program()
{
	glfwTerminate();
	exit(0);
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
*/

static int init_system_resources(t_software_environ *env, int argc, char **argv)
{
	getcwd(env->cwd, sizeof(env->cwd));

	if (argc != 2) {
		return (-1);
	}

	// Load provided object file
	if (load_object_file(&env->data, argv[1]) < 0)
		return (-1);

	// All OK
	return (0);
}

void init(t_software_environ *env, int argc, char **argv)
{
	WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
	WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

	(void)argv;
	(void)argc;

	glfwSetErrorCallback(error_callback);


	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return ;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SOFT_GLFW_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SOFT_GLFW_CONTEXT_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	WINDOW = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);

	if (!WINDOW) {
		glfwTerminate();
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		exit(1);
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
