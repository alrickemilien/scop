#include "scop.h"

t_software_environ *env = NULL;

/*
** This macro handles the fact that windows works with \ and not / as Unix
** when it comes to treat with files ...
*/

#ifdef _MSC_VER
static const char *vertex_file_path = "\x5c""shaders""\x5c""mesh""\x5c""VertexShader.glsl";
static const char *fragment_file_path = "\x5c""shaders""\x5c""mesh""\x5c""FragmentShader.glsl";

static const char *plan_vertex_file_path = "\x5c""shaders""\x5c""plan""\x5c""VertexShader.glsl";
static const char *plan_fragment_file_path = "\x5c""shaders""\x5c""plan""\x5c""FragmentShader.glsl";
static const char *plan_geometry_file_path = "\x5c""shaders""\x5c""plan""\x5c""GeometryShader.glsl";

static const char *axis_vertex_file_path = "\x5c""shaders""\x5c""axis""\x5c""VertexShader.glsl";
static const char *axis_fragment_file_path = "\x5c""shaders""\x5c""axis""\x5c""FragmentShader.glsl";
static const char *axis_geometry_file_path = "\x5c""shaders""\x5c""axis""\x5c""GeometryShader.glsl";

static const char *normals_vertex_file_path = "\x5c""shaders""\x5c""normals\x5c""VertexShader.glsl";
static const char *normals_fragment_file_path = "\x5c""shaders""\x5c""normals\x5c""FragmentShader.glsl";
static const char *normals_geometry_file_path = "\x5c""shaders""\x5c""normals\x5c""GeometryShader.glsl";

#else
static const char *vertex_file_path = "/shaders/mesh/VertexShader.glsl";
static const char *fragment_file_path = "/shaders/mesh/FragmentShader.glsl";

static const char *plan_vertex_file_path = "/shaders/plan/VertexShader.glsl";
static const char *plan_fragment_file_path = "/shaders/plan/FragmentShader.glsl";
static const char *plan_geometry_file_path = "/shaders/plan/GeometryShader.glsl";

static const char * axis_vertex_file_path = "/shaders/axis/VertexShader.glsl";
static const char * axis_fragment_file_path = "/shaders/axis/FragmentShader.glsl";
static const char * axis_geometry_file_path = "/shaders/axis/GeometryShader.glsl";

static const char *normals_vertex_file_path = "/shaders/normals/VertexShader.glsl";
static const char *normals_fragment_file_path = "/shaders/normals/FragmentShader.glsl";
static const char *normals_geometry_file_path = "/shaders/normals/GeometryShader.glsl";
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

void stop_on_sigint(int signo)
{
	if (signo == SIGINT && env != NULL)
		glfwSetWindowShouldClose(WINDOW, GLFW_TRUE);
}

/*
**
*/
void run()
{
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Load object shader

	memset(&env->object_shader_program, 0, sizeof(shader_program_t));
	memset(&env->internal_object_shader_program, 0, sizeof(shader_program_t));
	memset(&env->axis_shader_program, 0, sizeof(shader_program_t));
	memset(&env->normals_shader_program, 0, sizeof(shader_program_t));

	env->object_shader_program.cwd = (char*)env->cwd;
	env->internal_object_shader_program.cwd = (char*)env->cwd;
	env->axis_shader_program.cwd = (char*)env->cwd;
	env->normals_shader_program.cwd = (char*)env->cwd;

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

	if (load_program_shader(&env->normals_shader_program, normals_vertex_file_path, normals_fragment_file_path, normals_geometry_file_path) < 0)
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

	gl_lighting(env);

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

	if (argc < 2)
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

	// Load mtllib files if any provided
	if (load_mtllib(env->data.mtllib, env->data.usemtl) < 0)
		return (-1);

	if (argc > 2 && load_bitmap_file(&env->bmp, argv[2]) < 0)
		return (-1);

	count_vertices(&env->data);

	env->scale = 1.0f;
	env->y_auto_rotate_angle = 0.f;
	env->render_style = GL_TRIANGLES;
	env->indexation_mode = env->data.smooth_shading ? 1 : 0;
	env->ambient_lighting = 0.45f;
	env->specular_lighting = 0.5f;
	env->render_normals = true;

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

int main(int argc, char **argv)
{
	if (signal(SIGINT, stop_on_sigint) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGINT\n");

	// Could not continue if the system ressources are fully and successfully loaded
	if (init_system_resources(argc, argv) < 0)
		return (-1);

	// print_object((const void*)&env->data);

	init(argc, argv);

	run();

	return 0;
}
