#include "scop.h"

t_software_environ *env = NULL;

/*
** This macro handles the fact that windows works with \ and not / as Unix
** when it comes to treat with files ...
*/

#ifdef _MSC_VER
static const char *vertex_file_path = "\x5c""shaders""\x5c""SimpleVertexShader.glsl";
static const char *fragment_file_path = "\x5c""shaders""\x5c""SimpleFragmentShader.glsl";

static const char *plan_vertex_file_path = "\x5c""shaders""\x5c""plan""\x5c""VertexShader.glsl";
static const char *plan_fragment_file_path = "\x5c""shaders""\x5c""plan""\x5c""FragmentShader.glsl";
static const char *plan_geometry_file_path = "\x5c""shaders""\x5c""plan""\x5c""GeometryShader.glsl";

static const char * axis_vertex_file_path = "\x5c""shaders""\x5c""axis""\x5c""VertexShader.glsl";
static const char * axis_fragment_file_path = "\x5c""shaders""\x5c""axis""\x5c""FragmentShader.glsl";
static const char * axis_geometry_file_path = "\x5c""shaders""\x5c""axis""\x5c""GeometryShader.glsl";

#else
static const char *vertex_file_path = "/shaders/SimpleVertexShader.glsl";
static const char *fragment_file_path = "/shaders/SimpleFragmentShader.glsl";

static const char *plan_vertex_file_path = "/shader/plan/VertexShader.glsl";
static const char *plan_fragment_file_path = "/shader/plan/FragmentShader.glsl";
static const char *plan_geometry_file_path = "/shader/plan/GeometryShader.glsl";
#endif

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

static bool closing = false;

// Close OpenGL window and terminate GLFW
static void end_program(int code)
{
	if (closing)
		return ;

	closing = true;

	printf("Closing app ...\n");

	cleanup_shader_program(&env->object_shader_program);
	cleanup_shader_program(&env->internal_object_shader_program);

	// glDeleteBuffers(1, env->);
	// glDeleteVertexArrays(1, env->);

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
	// glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);

	// glEnable(GL_CULL_FACE); // cull face
	// glCullFace(GL_BACK); // cull back face
	// glFrontFace(GL_CW); // GL_CCW for counter clock-wise

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// print_object(&env->data);

	// Load object shader

	env->object_shader_program.cwd = (char*)env->cwd;
	env->internal_object_shader_program.cwd = (char*)env->cwd;
	env->axis_shader_program.cwd = (char*)env->cwd;

	if (load_program_shader(&env->object_shader_program, vertex_file_path, fragment_file_path, NULL) < 0)
	{
		end_program(-1);
		return ;
	}
	
	if (load_program_shader(&env->internal_object_shader_program, plan_vertex_file_path, plan_fragment_file_path, plan_geometry_file_path) < 0)
	{
		end_program(-1);
		return ;
	}

	if (load_program_shader(&env->axis_shader_program, axis_vertex_file_path, axis_fragment_file_path, axis_geometry_file_path) < 0)
	{
		end_program(-1);
		return ;
	}

	if (!env->indexation_mode && gl_buffering(env) < 0)
	{
		end_program(-1);
		return ;
	}
	
	if (env->indexation_mode && gl_indexing(env) < 0)
	{
		end_program(-1);
		return ;
	}

	gl_matrixing(env);

	printf("Preparation is done\n");

	// Check if the ESC key was pressed or the window was closed
	while (glfwWindowShouldClose(WINDOW) == 0)
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

	env->scale = 1;
	env->y_auto_rotate_angle = 0.f;
	env->render_style = GL_TRIANGLE_STRIP_ADJACENCY;
	env->indexation_mode = 1;

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

	glfwSetWindowSizeCallback(WINDOW, window_size_callback);
	glfwSetFramebufferSizeCallback(WINDOW, window_size_callback);

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
