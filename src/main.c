#include "scop.h"

t_software_environ *env = NULL;

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

/*
** Clear the environnement in memory
*/

static void del(void *p, size_t s) {
	(void)s;
	free(p);
}

void clear_env_memory() {
	printf("Clearing environnement ...\n");

	if (!env)
		return ;

	if(env->data.name)
		free(env->data.name);
	if(env->data.mtl)
		free(env->data.mtl);
	if(env->data.positions)
		ft_lstdel(&env->data.positions, &del);
	if(env->data.uvs)
		ft_lstdel(&env->data.uvs, &del);
	if(env->data.normals)
		ft_lstdel(&env->data.normals, &del);

	// @TODO ==> need to clear sublist
	if(env->data.polygons)
		ft_lstdel(&env->data.polygons, &del);

	free(env);
}

// Close OpenGL window and terminate GLFW
void	end_program()
{
	printf("Closing app ...\n");

	clear_env_memory();

	glDetachShader(env->program_id, env->vertex_shader_id);
	glDetachShader(env->program_id, env->fragment_shader_id);

	glDeleteShader(env->vertex_shader_id);
	glDeleteShader(env->fragment_shader_id);

	// glDeleteBuffers(1, env->);
	// glDeleteVertexArrays(1, env->);
	glDeleteProgram(env->program_id);

	glfwTerminate();

	printf("Closed.\n");

	exit(0);
}

/*
*/
void run()
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
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render(env);

		// Swap buffers
		glfwSwapBuffers(WINDOW);

		// Handle other events (mouse, keyboard, ...)
		glfwPollEvents();
	}

	end_program();
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s (%d)\n", description, error);
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

/*
** Initialize the system with the provided resources
** - Register the current
** - Find the shader folder and register the path
** - Read the resources into the object folder
** When all ok, start the application
*/

static int init_system_resources(int argc, char **argv)
{
	if (NULL == (env = malloc(sizeof(t_software_environ))))
		exit_error_with_message("Not enought memory to run the program");

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

void init(int argc, char **argv)
{
	WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
	WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

	(void)argv;
	(void)argc;

	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
		exit_error_with_message("Failed to initialize GLFW");

  // Se the antialiasing => pixels are subdivided by X
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
	// Could not continue if the system ressources are fully and successfully loaded
	if (init_system_resources(argc, argv) < 0)
		return (-1);

	init(argc, argv);

	run();

	return 0;
}
