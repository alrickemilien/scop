#include "scop.h"

typedef struct s_glx_attribute {
  const char *attribute_name;

  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  const GLvoid *pointer;
} t_glx_attribute;

// static const size_t polygon_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);
// static const size_t polygon_size = sizeof(GLfloat) * 6;

static const t_glx_attribute g_attribute_map[] = {
  {
    "position",
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(GLfloat) * 6,
    0
  },
  {
    "color",
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(GLfloat) * 6,
    (void*)(sizeof(t_vec3))
  },
  {
    "uv",
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(GLfloat) * 6,
    (void*)(sizeof(t_vec3) + sizeof(t_vec3))
  },
  {
    "normal",
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(GLfloat) * 6,
    (void*)(sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2))
  }
};

void set_attribute(GLuint id_program, const char *attribute_name)
{
  //GLuint	id;
  size_t  i;

  i = 0;
  while((i * sizeof(t_glx_attribute)) < sizeof(g_attribute_map))
  {
    if (memcmp(attribute_name,
          g_attribute_map[i].attribute_name,
          strlen(g_attribute_map[i].attribute_name)) == 0)
    {
    //  id = glGetAttribLocation(id_program,
    //                          g_attribute_map[i].attribute_name);

      glEnableVertexAttribArray(i);

      // glVertexAttribPointer(id_program,
      //   g_attribute_map[i].size​,
      //   g_attribute_map[i].type​,
      //   g_attribute_map[i].normalized,
      //   g_attribute_map[i].stride​,
      //   (void*)(g_attribute_map[i].pointer​));

			glBindAttribLocation(id_program, i, attribute_name);

      return ;
    }

    i++;
  }
}
