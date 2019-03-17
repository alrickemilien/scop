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

static void print_gl_shader_error(GLuint id, int info_log_length) {
	char *error_message;

	error_message = malloc(sizeof(char) * info_log_length);
	glGetShaderInfoLog(id, info_log_length, NULL, error_message);
	fprintf(stderr, "%s\n", error_message);
	free(error_message);
}

static void compile_single_shader(GLuint id, const shader_t *source, int *info_log_length, GLint *result)
{
	char *error_message;

	error_message = NULL;

	glShaderSource(id, 1, (const GLchar *const *)(&source->content), &source->length);
	glCompileShader(id);

	// Check Shader
	glGetShaderiv(id, GL_COMPILE_STATUS, result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, info_log_length);

	if (info_log_length > 0) {
		print_gl_shader_error(id, *info_log_length);
	}
}

/*
** Load shaders
*/

GLuint load_shaders(t_software_environ *env) {
	// Create the shaders variables
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	shader_t *vertex_shader_code;
	shader_t *fragment_shader_code;

	char *vertex_file_full_path;
	char *fragment_file_full_path;

	// Build full path of the shaders
	vertex_file_full_path = ft_strjoin(env->cwd, vertex_file_path);
	fragment_file_full_path = ft_strjoin(env->cwd, fragment_file_path);

	if (!vertex_file_full_path || !fragment_file_full_path)
		exit_error_with_message("An error occured when wanting to build shaders full path");

	// Read the Vertex Shader code from the file
	vertex_shader_code = load_single_shader(vertex_file_full_path, vertex_shader_id);

	// Read the Fragment Shader code from the file
	fragment_shader_code = load_single_shader(fragment_file_full_path, fragment_shader_id);

	printf("vertex_shader_code %.10s\n", (char*)vertex_shader_code->content);

	for(GLint i = 0; i < vertex_shader_code->length; i++)
	{
		printf("%c", ((char*)vertex_shader_code->content)[i]);
	}

	printf("\n");

	if (vertex_shader_code == NULL || fragment_shader_code == NULL)
		return (-1);

	GLint result = GL_FALSE;
	int info_log_length;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_full_path);

	compile_single_shader(vertex_shader_id, vertex_shader_code, &info_log_length, &result);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_full_path);

	compile_single_shader(fragment_shader_id, fragment_shader_code, &info_log_length, &result);

	// Link the program
	printf("Linking program\n");

	GLuint program_id = glCreateProgram();

	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	glLinkProgram(program_id);

	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length > 0) {
		print_gl_shader_error(program_id, info_log_length);
	}

	env->vertex_shader_id = vertex_shader_id;
	env->fragment_shader_id = fragment_shader_id;

	env->program_id = program_id;

	return (program_id);
}
