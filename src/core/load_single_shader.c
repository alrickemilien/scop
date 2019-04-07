#include "scop.h"

#ifdef __APPLE__

shader_t	*load_single_shader(const char *path, GLuint id)
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
		fprintf(stderr, "%s: File does not exist or permission denied\n", path);
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
		fprintf(stderr, "File does not exist or permission denied\n");
	}

	close(fd);

	return (shader);
}

#endif