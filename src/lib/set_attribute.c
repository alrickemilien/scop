#include "scop.h"

extern t_scop	g_scop;

//  void glVertexAttribPointer(GLuint index​, GLint size​, GLenum type​, GLboolean normalized​, GLsizei stride​, const GLvoid * pointer​)
typedef struct            s_glx_attribute {
               const char *attribute_name;
               GLint     size​;
               GLenum     type​;
               GLboolean     stride​;
               GLsizei     data_size;
               const GLvoid *pointer​;
}                         t_glx_attribute;

static const t_glx_attribute g_attribute_map[] = {
  {
    "position", 3, GL_FLOAT, GL_FALSE,
      sizeof(float) * 11, 0
  },
  {
    "color", 3, GL_FLOAT, GL_FALSE,
    sizeof(float) * 11, (void*)(sizeof(float) * 3)
  },
  {
    "uv", 2, GL_FLOAT, GL_FALSE,
    sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 6)
  },
  {
    "normal", 3, GL_FLOAT, GL_FALSE,
    sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 8)
  },
  {
    NULL, 0, 0, 0, 0
  }
};

void set_attribute(GLuint id_program, const char *attribute_name)
{
  GLuint	id;
  size_t  i;

  for (i = 0; g_attribute_map[i].attribute_name; i++) {
    if (memcmp(attribute_name,
          g_attribute_map[i].attribute_name,
          strlen(g_attribute_map[i].attribute_name)) == 0)
    {
      id = glGetAttribLocation(id_program,
                              g_attribute_map[i].attribute_name);

      glEnableVertexAttribArray(id);

      glVertexAttribPointer(id_program,
        g_attribute_map[i].size​,
        g_attribute_map[i].type​,
        g_attribute_map[i].stride​,
        g_attribute_map[i].data_size,
        (void*)(g_attribute_map[i].pointer​));

      return ;
    }
  }
}
