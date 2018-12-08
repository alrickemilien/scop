#include "scop.h"

static const char *vertex_file_path = "C:\\Users\\Thierry\\Documents\\Alrick\\scop\\shaders\\SimpleVertexShader.glsl";
static const char *fragment_file_path = "C:\\Users\\Thierry\\Documents\\Alrick\\scop\\shaders\\SimpleFragmentShader.glsl";

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

	return (ret);
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

	if (stat(path, &stats) == -1) {
		fprintf(stderr, "%s: Could not read file size\n", path);
		return (NULL);
	}

	shader->length = stats.st_size;

	if (shader->length == 0) {
		fprintf(stderr, "%s:Invalid file size\n", path);
		return (NULL);
	}

	shader->content = (char*)malloc(sizeof(char) * shader->length);

	if (shader->content == NULL)
		return (NULL);

	tmp = create_escaped_path_for_windows(path);

	if (NULL == (fd = CreateFile(
            tmp,
            GENERIC_READ,
            FILE_SHARE_READ,
   			NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
	))) {
		fprintf(stderr, "%s: CreateFile error - File does not exist or permission denied\n", path);

		return (NULL);
	}

	free(tmp);

	if (NULL == (hMapFile = CreateFileMapping(
		fd,
		0,
		PAGE_READONLY,
		0,
		shader->length,
		0
	)))
	{
		fprintf(stderr, "%s: CreateFileMapping error - File does not exist or permission denied\n", path);

		return (NULL);
	}

	printf("file size : %d\n", (int)shader->length);

	if (NULL == (memory_buffer = MapViewOfFile(
		hMapFile,
		FILE_MAP_READ,
		0,
		0,
		shader->length)))
	{
		fprintf(stderr, "MapViewOfFile error - File does not exist or permission denied\n");
		return (NULL);
	}

	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		printf("yaaaaa\n");
	}

	printf("memory buffer %.10s\n", (char*)memory_buffer);

	memcpy(shader->content, memory_buffer, shader->length);

	UnmapViewOfFile(memory_buffer);

	CloseHandle(hMapFile);

	CloseHandle(fd);

	return (shader);
}

void *mmap(char *address, size_t length, int file, off_t offset)
{
    void *map;
    HANDLE handle;

    map = (void *) NULL;
    handle = INVALID_HANDLE_VALUE;

    handle = CreateFileMapping((HANDLE) _get_osfhandle(file), 0, PAGE_READONLY, 0, length, 0);
    if (!handle)
           return (NULL);
    map = (void *) MapViewOfFile(handle, FILE_MAP_READ, 0, 0, length);
    CloseHandle(handle);

    if (map == (void *) NULL)
        return(NULL);
    return((void *) ((char *) map + offset));
}

#else
/**
 * https://github.com/icefox/netflixrecommenderframework/blob/b0315e13edab5f3095007cb018bb40686eb2e431/src/winmmap.h
 */

// static void	*test(const char *path)
// {
// 	int			fd;
// 	struct stat	stats;
// 	int length;
// 	void *content;
//
// 	if ((fd = open(path, O_RDONLY)) == -1)
// 	{
// 		fprintf(stderr, "%s: open - File does not exist or permission denied\n", path);
// 		return (NULL);
// 	}
//
// 	if (fstat(fd, &stats) == -1)
// 		return (NULL);
//
// 	if (stats.st_size <= 0)
// 		return (NULL);
//
// 	length = stats.st_size;
//
// 	if (NULL == (content = mmap(NULL, length, fd, 0)))
// 	{
// 		fprintf(stderr, "mmap - File does not exist or permission denied\n");
// 	}
//
// 	close(fd);
// 	return (content);
// }
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

GLuint load_shaders(void) {
	// Create the shaders variables
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	shader_t *vertex_shader_code;
	shader_t *fragment_shader_code;

	// Read the Vertex Shader code from the file
	vertex_shader_code = load_single_shader(vertex_file_path, vertex_shader_id);

	// void *map = test(vertex_file_path);
	//
	// printf("LOOOOL : %.20s\n", map);
	// free(map);

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

	return program_id;
}
