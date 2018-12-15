#include "scop.h"

static const char *vertex_file_path = "./shaders/SimpleVertexShader.glsl";
static const char *fragment_file_path = "./shaders/SimpleFragmentShader.glsl";

typedef struct	shader_s {
	GLuint		id;
	GLchar		*content;
	GLint		length;
}				shader_t;

static shader_t	*load_single_shader(const char *path, GLuint id)
{
	int			fd;
	shader_t	*shader;
	struct stat	stats;


	shader = malloc(sizeof(shader_t));

	if (shader == NULL)
		return (NULL);

	shader->id = id;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		dprintf(2, "%s: File does not exist or permission denied\n", path);
		return (NULL);
	}

	if (fstat(fd, &stats) == -1)
		return (NULL);

	if (stats.st_size <= 0)
		return (NULL);

	shader->length = stats.st_size;

	if (MAP_FAILED == (shader->content = mmap(NULL, shader->length,
		PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
		dprintf(2, "File does not exist or permission denied\n");
	}

	close(fd);

	return (shader);
}

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

GLuint load_shaders(void) {
	// Create the shaders variables
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	shader_t *vertex_shader_code;
	shader_t *fragment_shader_code;

	// Read the Vertex Shader code from the file
	vertex_shader_code = load_single_shader(vertex_file_path, vertex_shader_id);

	// Read the Fragment Shader code from the file
	fragment_shader_code = load_single_shader(fragment_file_path, fragment_shader_id);

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
	printf("Compiling shader : %s\n", vertex_file_path);

	compile_single_shader(vertex_shader_id, vertex_shader_code, &info_log_length, &result);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);

	compile_single_shader(vertex_shader_id, fragment_shader_code, &info_log_length, &result);

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

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return (program_id);
}
