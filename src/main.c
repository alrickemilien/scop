#include "scop.h"

t_software_environ *env = NULL;

static void glew_init(void)
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

/*
** Clear the environnement in memory
*/

static void del(void *p, size_t s)
{
	(void)s;
	free(p);
}

static void clear_env_memory()
{
	printf("Clearing environnement ...\n");

	if (!env)
		return;

	if (env->data.name)
		free(env->data.name);
	if (env->data.mtl)
		free(env->data.mtl);
	if (env->data.positions)
		ft_lstdel(&env->data.positions, &del);
	if (env->data.uvs)
		ft_lstdel(&env->data.uvs, &del);
	if (env->data.normals)
		ft_lstdel(&env->data.normals, &del);

	// @TODO ==> need to clear sublist
	if (env->data.polygons)
		ft_lstdel(&env->data.polygons, &del);

	free(env);
}

// Close OpenGL window and terminate GLFW
static void end_program(int code)
{
	printf("Closing app ...\n");

	glDetachShader(env->program_id, env->vertex_shader_id);

	glDetachShader(env->program_id, env->fragment_shader_id);

	glDeleteShader(env->vertex_shader_id);
	glDeleteShader(env->fragment_shader_id);

	// glDeleteBuffers(1, env->);
	// glDeleteVertexArrays(1, env->);
	glDeleteProgram(env->program_id);

	glfwTerminate();

	clear_env_memory();

	printf("Closed.\n");

	exit(code);
}

void stop_on_sigint(int signo)
{
	if (signo == SIGINT && env != NULL)
	{
		glfwSetWindowShouldClose(WINDOW, GLFW_TRUE);
	}
}

/*
**
*/
void run()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	print_object(&env->data);


	if (load_shaders(env) < 0) {
		end_program(-1);
		return;
	}

	gl_buffering(env);

	printf("Preparation is done\n");

	// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(WINDOW, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		   glfwWindowShouldClose(WINDOW) == 0)
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render(env);

		// Handle other events (mouse, keyboard, ...)
		glfwPollEvents();

		// Swap buffers
		glfwSwapBuffers(WINDOW);
	}

	end_program(0);
}

static void glfw_error_callback(int error, const char *description)
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

#ifdef __APPLE__
	if (getcwd(env->cwd, sizeof(env->cwd)) == NULL)
		exit_error_with_message("An error occured when oading the pwd path of the program.");
#else
	if (_getcwd(env->cwd, sizeof(env->cwd)) == NULL)
		exit_error_with_message("An error occured when oading the pwd path of the program.");
#endif

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
	};

	// Ensure we can capture the escape key being pressed below
	//	glfwSetInputMode(WINDOW, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetKeyCallback(WINDOW, key_callback);

	glfwMakeContextCurrent(WINDOW);
	
	printf("OpenGL %s, GLSL %s\n", 
    		glGetString(GL_VERSION),
    		glGetString(GL_SHADING_LANGUAGE_VERSION));

	glew_init();
}

int main(int argc, char **argv)
{
	if (signal(SIGINT, stop_on_sigint) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGINT\n");

	// Could not continue if the system ressources are fully and successfully loaded
	if (init_system_resources(argc, argv) < 0)
		return (-1);


	// printf("env->data.vertex_count : %ld\n", env->data.vertex_count);

	// print_object((const void*)&env->data);

	init(argc, argv);

	run();

	return 0;
}
