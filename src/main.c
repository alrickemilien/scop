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

	fill_uvs(env->data.polygons);

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

	printf("gl_buffering done\n");
	check_gl_error();

	gl_matrixing(env);

		printf("matrixing done\n");
	check_gl_error();

	gl_texturing(env);

		printf("textureuing done\n");
	check_gl_error();

	gl_lighting(env);

		printf("lighting done\n");
	check_gl_error();

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

int main(int argc, char **argv)
{
	if (NULL == (env = malloc(sizeof(t_software_environ))))
		exit_error_with_message("Not enought memory to run the program");

	if (signal(SIGINT, stop_on_sigint) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGINT\n");

	// Could not continue if the system ressources are fully and successfully loaded
	if (system_init(env, argc, argv) < 0)
		return (-1);

	// print_object((const void*)&env->data);

	glfw_init(env, argc, argv);

	run();

	end_program(0);

	return (0);
}
