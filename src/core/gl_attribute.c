#include "scop.h"

typedef struct s_glx_attribute {
  const char *attribute_name;

  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  const GLvoid *pointer;
} t_glx_attribute;

//#define VERTEX_SIZE 3 * sizeof(t_vec3) + sizeof(t_vec2)
#define VERTEX_SIZE sizeof(t_vec3)

static const t_glx_attribute g_attribute_map[] = {
  {
    "position",
    3,
    GL_FLOAT,
    GL_FALSE,
    VERTEX_SIZE,
    0
  },
  {
    "color",
    3,
    GL_FLOAT,
    GL_FALSE,
    VERTEX_SIZE,
    (char *)NULL + (sizeof(t_vec3))
  },
  {
    "uv",
    2,
    GL_FLOAT,
    GL_FALSE,
    VERTEX_SIZE,
    (char *)NULL + (sizeof(t_vec3) + sizeof(t_vec3))
  },
  {
    "normal",
    3,
    GL_FLOAT,
    GL_FALSE,
    VERTEX_SIZE,
    (char *)NULL + (sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2))
  }
};

void set_attribute(GLuint id_program, const char *attribute_name)
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

			id = glGetAttribLocation(id_program, g_attribute_map[i].attribute_name);

      fprintf(stderr, "glGetAttribLocation returned id : %d\n", id);

			// glBindAttribLocation(id_program, i, g_attribute_map[i].attribute_name);

     // id = (GLint)i;

			// If the named attribute variable is not an active attribute in the specified program object
			// if (id == -1) {
			//
			// }
			check_gl_error();

			glEnableVertexAttribArray(id);

			fprintf(stderr, "id : %d\n", id);

      glVertexAttribPointer(id,
        g_attribute_map[i].size,
				g_attribute_map[i].type,
        g_attribute_map[i].normalized,
        g_attribute_map[i].stride,
				(void*)(g_attribute_map[i].pointer));

			check_gl_error();

      return ;
    }

    i++;
  }
}