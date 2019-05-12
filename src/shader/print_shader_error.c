#include "scop.h"

void print_gl_shader_error(GLuint id, int info_log_length)
{
	char *error_message;

	error_message = malloc(sizeof(char) * info_log_length + 1);
	error_message[sizeof(char) * info_log_length] = 0;
	glGetShaderInfoLog(id, sizeof(char) * info_log_length, NULL, error_message);
	fprintf(stderr, "gl_shader_error : %s\n", error_message);
	free(error_message);
}

void print_gl_program_error(GLuint id, int info_log_length)
{
	char *error_message;

	error_message = malloc(sizeof(char) * info_log_length + 1);
	error_message[sizeof(char) * info_log_length] = 0;
	glGetProgramInfoLog(id, sizeof(char) * info_log_length, NULL, error_message);
	fprintf(stderr, "gl_program_error : %s\n", error_message);
	free(error_message);
}