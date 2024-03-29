#include "scop.h"

/*
** typedef struct	shader_s {
** 	GLuint		id;
** 	GLchar		*content;
** 	GLint		length;
** }				shader_t;
*/

static shader_t	*load_shader(GLenum shader_type, char *src_path)
{
	GLint		result;
	int			info_log_length;
	shader_t	*shader;

	if (src_path == NULL)
	{
		fprintf(stderr,
			"An error occured when wanting to build shaders full path");
		return (NULL);
	}
	if (NULL == (shader = (shader_t*)malloc(sizeof(shader_t))))
		return (NULL);
	shader->path = src_path;
	shader->id = glCreateShader(shader_type);
	if (load_single_shader(shader, shader->path) < 0)
		return (NULL);
	result = GL_FALSE;
	info_log_length = 0;
	if (compile_single_shader(shader, &info_log_length, &result) < 0)
		return (NULL);
	return (shader);
}

static int		link_program(
		shader_program_t *program)
{
	GLint	result;
	int		info_log_length;

	glLinkProgram(program->id);
	glGetProgramiv(program->id, GL_LINK_STATUS, &result);
	glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (result == GL_FALSE)
	{
		print_gl_program_error(program->id, info_log_length);
		return (-1);
	}
	return (0);
}

/*
** Load shaders
*/

int				load_program_shader(
		shader_program_t *program,
		const char *vertex,
		const char *fragment,
		const char *geometry)
{
	program->id = glCreateProgram();
	program->vertex_shader = NULL;
	program->fragment_shader = NULL;
	program->geometry_shader = NULL;
	if (vertex && (program->vertex_shader = load_shader(
			GL_VERTEX_SHADER, ft_strjoin(program->cwd, vertex))) == NULL)
		return (-1);
	if (fragment && (program->fragment_shader = load_shader(
			GL_FRAGMENT_SHADER, ft_strjoin(program->cwd, fragment))) == NULL)
		return (-1);
	if (geometry && (program->geometry_shader = load_shader(
			GL_GEOMETRY_SHADER, ft_strjoin(program->cwd, geometry))) == NULL)
		return (-1);
	if (vertex)
		glAttachShader(program->id, program->vertex_shader->id);
	if (fragment)
		glAttachShader(program->id, program->fragment_shader->id);
	if (geometry)
		glAttachShader(program->id, program->geometry_shader->id);
	return (link_program(program));
}
