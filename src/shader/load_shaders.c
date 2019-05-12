#include "scop.h"

/*
** This macro handles the fact that windows works with \ and not / as Unix
** when it comes to treat with files ...
*/

#ifdef _MSC_VER
static const char *vertex_file_path = "\x5cshaders\x5cSimpleVertexShader.glsl";
static const char *fragment_file_path = "\x5cshaders\x5cSimpleFragmentShader.glsl";
#else
static const char *vertex_file_path = "/shaders/SimpleVertexShader.glsl";
static const char *fragment_file_path = "/shaders/SimpleFragmentShader.glsl";
#endif

/*
** typedef struct	shader_s {
** 	GLuint		id;
** 	GLchar		*content;
** 	GLint		length;
** }				shader_t;
*/

static int load_shader(t_software_environ *env, shader_t *shader, GLenum shader_type, const char *src_path)
{
	char *full_path;
	GLuint shader_id;
	GLint result;
	int info_log_length;
	
	shader_id = glCreateShader(shader_type);

	full_path = ft_strjoin(env->cwd, src_path);

	if (full_path == NULL)
		exit_error_with_message("An error occured when wanting to build shaders full path");

	shader = load_single_shader(full_path, shader_id);

	result = GL_FALSE;
	info_log_length = 0;
	if (compile_single_shader(shader_id, shader, &info_log_length, &result) < 0)
		return (-1);

	return (1);
}

/*
** Load shaders
*/

int load_shaders(t_software_environ *env) {
	// Create the shaders variables
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	shader_t *vertex_shader_code;
	shader_t *fragment_shader_code;

	char *vertex_file_full_path;
	char *fragment_file_full_path;

	// Build full path of the shaders
	vertex_file_full_path = ft_strjoin(env->cwd, vertex_file_path);
	char *vertex_file_full_path;
	fragment_file_full_path = ft_strjoin(env->cwd, fragment_file_path);

	if (!vertex_file_full_path || !fragment_file_full_path)
		exit_error_with_message("An error occured when wanting to build shaders full path");

	// Read the Vertex Shader code from the file
	vertex_shader_code = load_single_shader(vertex_file_full_path, vertex_shader_id);

	// Read the Fragment Shader code from the file
	fragment_shader_code = load_single_shader(fragment_file_full_path, fragment_shader_id);

	printf("vertex_shader_code length : %d\n", vertex_shader_code->length);
	printf("vertex_shader_code content :\n");

	for(GLint i = 0; i < vertex_shader_code->length; i++)
	{
		printf("%c", ((char*)vertex_shader_code->content)[i]);
	}

	printf("\n");

	if (vertex_shader_code == NULL || fragment_shader_code == NULL)
		return (-1);

	GLint result = GL_FALSE;
	int info_log_length = 0;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_full_path);

	if (compile_single_shader(vertex_shader_id, vertex_shader_code, &info_log_length, &result) < 0)
		return (-1);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_full_path);

	if (compile_single_shader(fragment_shader_id, fragment_shader_code, &info_log_length, &result) < 0)
		return (-1);

	// Link the program
	printf("Linking program\n");

	GLuint program_id = glCreateProgram();

	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	glLinkProgram(program_id);

	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (result == GL_FALSE)
	{
		print_gl_program_error(program_id, info_log_length);
		return (-1);
	}

	env->vertex_shader_id = vertex_shader_id;
	env->fragment_shader_id = fragment_shader_id;

	env->program_id = program_id;

	return (0);
}