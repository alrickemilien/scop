#include "scop.h"
#ifdef _MSC_VER
static const char *vertex_file_path = "C:\\Users\\Thierry\\Documents\\Alrick\\scop\\shaders\\SimpleVertexShader.glsl";
static const char *fragment_file_path = "C:\\Users\\Thierry\\Documents\\Alrick\\scop\\shaders\\SimpleFragmentShader.glsl";
#else
#endif

typedef struct	shader_s {
	GLuint		id;
	GLchar		*content;
	GLint		length;
}				shader_t;

static int		count_char_into_string(const char *str, const char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			n++;
		i++;
	}

	return (n);
}

/*
** This function esacpe all backslashes for windows paths
** "C:\\Users\\Alrick\\scop\\shaders\\SimpleFragmentShader.glsl"
** becomes "C:\\\Users\\\Alrick\\\scop\\\shaders\\\SimpleFragmentShader.glsl"
*/
char*	create_escaped_path_for_windows(const char *path)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (count_char_into_string(path, 0x5C) + strlen(path)));

	if (ret == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (path[i])
	{
		ret[j] = path[i];

		if (path[i] == 0x5C) {
			j++;
			ret[j] = 0x5C;
		}

		i++;
		j++;
	}
}

/*
** Fuck windows
*/
#ifdef _MSC_VER
static shader_t	*load_single_shader(const char *path, GLuint id)
{
	HANDLE		fd;
	HANDLE		hMapFile;
	struct stat	stats;
	shader_t	*shader;
	void	 	*memory_buffer;
	char		*tmp;

	shader = malloc(sizeof(shader_t));

	if (shader == NULL)
		return (NULL);

	shader->id = id;

	tmp = create_escaped_path_for_windows(path);

	if ((fd = CreateFile(
            tmp,
            GENERIC_READ,
            FILE_SHARE_READ,
   			NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_READONLY,
            NULL
	)) == NULL) {
		fprintf(stderr, "%s: File does not exist or permission denied\n", path);

		return (NULL);
	}

	if ((hMapFile = CreateFileMapping(fd,
		NULL,
		PAGE_READONLY,
		0,
		0,
		NULL)) == NULL)
	{
		fprintf(stderr, "%s: File does not exist or permission denied\n", path);

		return (NULL);
	}

	free(tmp);

	if (stat(path, &stats) == -1) {
		fprintf(stderr, "%s: Could not read file size\n", path);
		return (NULL);
	}

	shader->length = stats.st_size;

	if (shader->length == 0) {
		fprintf(stderr, "%s:Invalid file size\n", path);
		return (NULL);
	}

	shader->content = malloc(sizeof(char) * (shader->length + 1));

	if (shader->content == NULL)
		return (NULL);

	printf("file size : %d\n", shader->length);

	if (NULL == (memory_buffer = MapViewOfFile(hMapFile,
		FILE_MAP_READ,
		0,
		0,
		shader->length + 1)))
	{
		fprintf(stderr, "File does not exist or permission denied\n");
		return (NULL);
	}

	memcpy(shader->content, memory_buffer, shader->length + 1);

	UnmapViewOfFile(memory_buffer);

	CloseHandle(fd);

	return (shader);
}
#else
static shader_t	*load_single_shader(const char *path)
{
	int			fd;
	shader_t	*shader;
	struct stat	stats;

	shader = malloc(sizeof(shader_t));

	if (shader == NULL)
		return (NULL);

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
	return (map);
}
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

	glShaderSource(id, 1, &source->content, &source->length);
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
	char *program_error_message;

	// Create the shaders variables
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	shader_t *vertex_shader_code;
	shader_t *fragment_shader_code;

	// Read the Vertex Shader code from the file
	vertex_shader_code = load_single_shader(vertex_file_path, vertex_shader_id);

	// Read the Fragment Shader code from the file
	fragment_shader_code = load_single_shader(fragment_file_path, fragment_shader_id);

	printf("vertex_shader_code %.10s\n", vertex_shader_code->content);

	
	for(size_t i = 0; i < vertex_shader_code->length; i++)
	{
		printf("%c", vertex_shader_code->content[i]);
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
		glGetProgramInfoLog(program_id, info_log_length, NULL, program_error_message);
		printf("%s\n", program_error_message);
	}

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}