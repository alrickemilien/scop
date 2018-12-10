#include "scop.h"

void	load_texture(
  GLuint shader_id,
  const char *texture_path,
  GLuint *texture_dest)
{
	size_t				 width;
	size_t				 height;
	unsigned char  *image_bytes_buffer;
  GLuint         texture_dest;

	glGenTextures(1, texture_dest);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture_dest);

  image_bytes_buffer = load_bitmap_file(texture_path, &width, &height);

  glTexImage2D(GL_TEXTURE_2D,
    0,
    GL_RGB,
    width,
    height,
    0,
    GL_BGR,
		GL_UNSIGNED_BYTE,
    image_bytes_buffer);

  // Destroy bytes buffer
  free(image_bytes_buffer);

  // The variable name texture into the shader
  glUniform1i(glGetUniformLocation(shader_id, "texture"), 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
