#include "scop.h"

static const t_glx_attribute	g_attribute_map[] = {
	{"position", 3, GL_FLOAT, GL_FALSE, 0},
	{"color", 3, GL_FLOAT, GL_FALSE, (uint8_t *) NULL + (sizeof(t_vec3))},
	{"normal", 3, GL_FLOAT, GL_FALSE, (uint8_t *) NULL + (sizeof(t_vec3) + sizeof(t_vec3))},
	{
		"uv",
		2,
		GL_FLOAT,
		GL_FALSE,
		(uint8_t *) NULL + (sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec3)),
	}
};

int								set_attribute(
	GLuint id_program,
	const char *attribute_name,
	size_t vertex_size)
{
	size_t	i;

	i = 0;
	while ((i * sizeof(t_glx_attribute)) < sizeof(g_attribute_map))
	{
		if (memcmp(attribute_name, g_attribute_map[i].attribute_name,
		           strlen(g_attribute_map[i].attribute_name)) == 0)
		{
			printf("id_program : %d\n", id_program);
			glBindAttribLocation(id_program, (GLuint) i,
			                     (const GLchar *) g_attribute_map[i].attribute_name);
			fprintf(stderr, "glGetAttribLocation returned id : %ld\n", i);
			fprintf(stderr, "attribute name : %s\n", attribute_name);
			if (check_gl_error() < 0)
				return (-1);
			glEnableVertexAttribArray(i);
			if (check_gl_error() < 0)
				return (-1);
			fprintf(stderr, "id : %ld\n", i);
			fprintf(stderr, "g_attribute_map[i].attribute_name : %s\n",
			        g_attribute_map[i].attribute_name);
			glVertexAttribPointer(i, g_attribute_map[i].size, g_attribute_map[i].type,
			                      g_attribute_map[i].normalized, (GLsizei) vertex_size,
			                      (void *) (g_attribute_map[i].pointer));
			if (check_gl_error() < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
