#include "scop.h"

//  void glVertexAttribPointer(GLuint index​, GLint size​, GLenum type​, GLboolean normalized​, GLsizei stride​, const GLvoid * pointer​)
typedef struct  s_glx_attribute {
								const char    *attribute_name;

								// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant GL_BGRA is accepted by glVertexAttribPointer. The initial value is 4.
								GLint         size​;
								GLenum        type​;

								// Set to true if normalized data
								GLboolean     normalized;

								// Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
								GLsizei       stride​;

								// Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
								const GLvoid  *pointer​;
}               t_glx_attribute;

static const size_t polygon_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);

static const t_glx_attribute g_attribute_map[] = {
  {
    "position",
		3,
		GL_FLOAT,

		// Not normalized
		GL_FALSE,
    polygon_size,
		0
  },
  {
    "color",
		3,
		GL_FLOAT,

		// Not normalized
		GL_FALSE,
    polygon_size,
		(void*)(sizeof(t_vec3))
  },
  {
    "uv",
		2,
		GL_FLOAT,

		// Not normalized
		GL_FALSE,
    polygon_size,
		(void*)(sizeof(t_vec3) + sizeof(t_vec3))
  },
  {
    "normal",
		3,
		GL_FLOAT,

		// Not normalized
		GL_FALSE,
    polygon_size,
		(void*)(sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2))
  },
};

void set_attribute(GLuint id_program, const char *attribute_name)
{
  GLuint	id;
  size_t  i;

  for (i = 0; i * sizeof(t_glx_attribute) < sizeof(g_attribute_map); i++) {
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
        g_attribute_map[i].normalized,
        g_attribute_map[i].stride​,
        (void*)(g_attribute_map[i].pointer​));

      return ;
    }
  }
}
