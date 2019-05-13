#include "scop.h"

#include <errno.h>
#include <string.h>

#ifdef _MSC_VER

int	load_single_shader(shader_t *shader, const char *path)
{
	FILE *f;
	struct stat	stats;

	if (stat(path, &stats) == -1) {
		fprintf(stderr, "%s: Could not read file size\n", path);
		return (-1);
	}

	shader->length = stats.st_size;

	if (shader->length == 0) {
		fprintf(stderr, "%s:Invalid file size\n", path);
		return (-1);
	}

	shader->content = (char*)malloc(sizeof(char) * shader->length + sizeof(char));

	if (shader->content == NULL) {
		free(shader);
		return (-1);
	}

	memset(shader->content, 0, sizeof(char) * shader->length + sizeof(char));

	f = fopen(path, "r");

	if (f == NULL) {
		fprintf(stderr, "Shader IO error : %s\n", strerror(errno));
		free(shader->content);
		free(shader);
		return (-1);		
	}
	
	fread(shader->content, shader->length, sizeof(char), f);

	if (fclose(f) < 0)
	{
		fprintf(stderr, "Shader IO error : %s\n", strerror(errno));
		return (-1);
	}

	return (0);
}

#endif
