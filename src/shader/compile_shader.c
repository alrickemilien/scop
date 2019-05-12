#include "scop.h"

int compile_single_shader(GLuint id, const shader_t *source, int *info_log_length, GLint *result)
{
	glShaderSource(id, 1, (const GLchar *const*)(&source->content), &source->length);
	glCompileShader(id);

	// Check Shader compilation
	glGetShaderiv(id, GL_COMPILE_STATUS, result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, info_log_length);

	if (*result == GL_FALSE) {
		print_gl_shader_error(id, *info_log_length);
		return (-1);
	}

	return (0);
}