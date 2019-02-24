#ifdef _MSC_VER

#include "scop.h"

/*
** Fuck windows
*/

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

void *mmap(char *address, size_t length, int file, int flags, int fildes, off_t offset)
{
    void *map;
    HANDLE handle;

	(void)flags;
	(void)fildes;

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

#endif
