#include "scop.h"

#ifdef __APPLE__
int		load_single_shader(
	shader_t *shader,
	const char *path)
{
	int			fd;
	struct stat	stats;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		fprintf(stderr, "%s: File does not exist or permission denied\n", path);
		return (-1);
	}
	if (fstat(fd, &stats) == -1 || stats.st_size <= 0)
		return (-1);
	shader->length = stats.st_size;
	if (MAP_FAILED == (shader->content = mmap(NULL, shader->length,
		PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
		fprintf(stderr, "File %s does not exist or permission denied\n", path);
		return (-1);
	}
	if (close(fd) < 0)
	{
		fprintf(stderr, "Unable to close file %s\n", path);
		return (-1);
	}
	return (0);
}
#endif
