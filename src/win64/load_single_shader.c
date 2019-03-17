#include "scop.h"

#ifdef _MSC_VER

shader_t	*load_single_shader(const char *path, GLuint id)
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

#endif
