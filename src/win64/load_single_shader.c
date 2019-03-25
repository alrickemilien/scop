#include "scop.h"

#include <errno.h>
#include <string.h>

#ifdef _MSC_VER

shader_t	*load_single_shader(const char *path, GLuint id)
{
	FILE *f;
	struct stat	stats;
	shader_t	*shader;

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

	shader->content = (char*)malloc(sizeof(char) * shader->length + sizeof(char));

	if (shader->content == NULL) {
		free(shader);
		return (NULL);
	}

	memset(shader->content, 0, sizeof(char) * shader->length + sizeof(char));

	f = fopen(path, "r");

	if (f == NULL) {
		fprintf(stderr, "Shader IO error : %s\n", strerror(errno));
		free(shader->content);
		free(shader);
		return NULL;		
	}
	
	fread(shader->content, shader->length, sizeof(char), f);

	fclose(f);

	return (shader);
}

#endif
