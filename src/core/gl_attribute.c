#include "scop.h"

typedef struct s_glx_attribute {
  const char *attribute_name;

  GLint size;
  GLenum type;
  GLboolean normalized;
  const GLvoid *pointer;
} t_glx_attribute;

static const t_glx_attribute g_attribute_map[] = {
  {
    "position",
    3,
    GL_FLOAT,
    GL_FALSE,
    0
  },
  {
    "color",
    3,
    GL_FLOAT,
    GL_FALSE,
    (uint8_t *)NULL + (sizeof(t_vec3))
  },
  {
    "uv",
    2,
    GL_FLOAT,
    GL_FALSE,
    (uint8_t *)NULL + (sizeof(t_vec3) + sizeof(t_vec3))
  },
  {
    "normal",
    3,
    GL_FLOAT,
    GL_FALSE,
    (uint8_t *)NULL + (sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2))
  }
};

int set_attribute(GLuint id_program, const char *attribute_name, size_t vertex_size)
{
  GLuint	id;
  size_t  i;

  i = 0;
  while((i * sizeof(t_glx_attribute)) < sizeof(g_attribute_map))
  {
    if (memcmp(attribute_name,
          g_attribute_map[i].attribute_name,
          strlen(g_attribute_map[i].attribute_name)) == 0)
    {

      printf("id_program : %d\n", id_program);

			id = glGetAttribLocation(id_program, g_attribute_map[i].attribute_name);

      fprintf(stderr, "glGetAttribLocation returned id : %d\n", id);

			// glBindAttribLocation(id_program, i, g_attribute_map[i].attribute_name);

     // id = (GLint)i;

			// If the named attribute variable is not an active attribute in the specified program object
			// if (id == -1) {
			//
			// }
			if (check_gl_error() < 0)
        return (-1);

			glEnableVertexAttribArray(id);

			fprintf(stderr, "id : %d\n", id);
			fprintf(stderr, "g_attribute_map[i].attribute_name : %s\n", g_attribute_map[i].attribute_name);

      glVertexAttribPointer(id,
        g_attribute_map[i].size,
				g_attribute_map[i].type,
        g_attribute_map[i].normalized,
        (GLsizei)vertex_size,
				(void*)(g_attribute_map[i].pointer));

			if (check_gl_error() < 0)
        return (-1);
    }

    i++;
  }

  return (0);
}
