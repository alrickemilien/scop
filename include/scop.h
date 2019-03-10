#ifndef SCOP_H
#define SCOP_H

/**
**       ___  ____  _____ _   _  ____ _       ___ _   _  ____ _    _   _ ____  _____ ____
**      / _ \|  _ \| ____| \ | |/ ___| |     |_ _| \ | |/ ___| |  | | | |  _ \| ____/ ___|
**     | | | | |_) |  _| |  \| | |  _| |      | ||  \| | |   | |  | | | | | | |  _| \___ \
**     | |_| |  __/| |___| |\  | |_| | |___   | || |\  | |___| |__| |_| | |_| | |___ ___) |
**      \___/|_|   |_____|_| \_|\____|_____| |___|_| \_|\____|_____\___/|____/|_____|____/
**
*/

# ifdef __APPLE__

/*
** GLFW3 already includes opengl.h gl.h etc.
*/

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <sys/mman.h>


# else

# include <GL/glew.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <GLFW/glfw3.h>

# endif

/*
**           __  __ ____   ____ __     _______ ____
**          |  \/  / ___| / ___|\ \   / / ____|  _ \
**          | |\/| \___ \| |     \ \ / /|  _| | |_) |
**          | |  | |___) | |___   \ V / | |___|  _ <
**      ____|_|  |_|____/ \____|___\_/  |_____|_| \_\
**     |_____|                |_____|
*/

#ifdef _MSC_VER

# include <windows.h>
# include <io.h>

#define _USE_MATH_DEFINES // for C
#include <math.h>

# define PATH_MAX 255

# define PROT_READ  1
# define PROT_WRITE  2
# define PROT_READWRITE  3
# define MAP_SHARED  1
# define MAP_PRIVATE  2
# define F_OK 0
# define R_OK 4
# define W_OK 2
# define RW_OK 6

# ifndef MAP_FAILED
# define MAP_FAILED      ((void *) -1)
# endif

typedef long int off_t;

void	*mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t offset);

int		munmap(void *addr, size_t len);

# endif

#ifndef _MSC_VER
# include <unistd.h>
# endif

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

/*
** LOCALS INCLUDES
*/

# include "utils.h"
# include "libmatrix.h"
# include "object_loader.h"

/*
** MACROS to access more easily to x server pointeurs to variables
** that will be always manipulated
** like x_server, window, image_buffer, etc
*/
# define WINDOW env->window
# define WINDOW_WIDTH env->window_width
# define WINDOW_HEIGHT env->window_height
# define WINDOW_NAME "scop"

# define SOFT_GLFW_CONTEXT_VERSION_MAJOR 4
# define SOFT_GLFW_CONTEXT_VERSION_MINOR 1

typedef struct	shader_s {
	GLuint		id;
	GLchar		*content;
	GLint		length;
}				shader_t;

typedef struct	s_light
{
	t_vec3		position;
	t_vec3		color;
}				t_light;

typedef struct	s_software_environ
{
	int			window_width;
	int			window_height;
	GLFWwindow     *window;

	// Path to the current directory where the binary file ./scop is executed
	char 					cwd[PATH_MAX];

	// The data that will be flled during object file loading
	t_obj_data		data;

	t_light				light;

	// Scop options that can evolve during software run
	int wireframe;
	int auto_rotate;
	int	lighting;
	int texturing;

	const char *path_to_texture;

	// OpenGL progrm id
	GLuint		program_id;

	// OpenGL VAO and VBO
	GLuint		vao;

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;

	// OpenGL shaders variables
	GLuint		mvp_uni;
	GLuint		model_matrix_uni;
	GLuint		lighting_uni;
	GLuint		light_position_uni;
	GLuint		texture_level;
	GLuint		light_color_uni;
	GLuint		texture_level_uni;
	GLuint		pos_attrib;
	GLuint		col_attrib;
	GLuint		texture;

	t_matrix *view_matrix;
	t_matrix *model_matrix;
	t_matrix *projection_matrix;
} t_software_environ;


typedef struct	s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
} t_color;

# define DEFAULT_WINDOW_WIDTH 600
# define DEFAULT_WINDOW_HEIGHT 600

/*
**                    _     _        __
**      ___      __ _| |   (_)_ __  / _| ___
**     / __|    / _` | |   | | '_ \| |_ / _ \
**     \__ \   | (_| | |   | | | | |  _| (_) |
**     |___/____\__, |_|___|_|_| |_|_|  \___/
**        |_____|___/ |_____|
*/

typedef struct s_gl_info {
	const char *vendor;
	const char *renderer;
	const char *version;
	const char *extensions;
	const char *glsl_version;

	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;
	int depthBits;
	int stencilBits;
	int maxLights;
	int maxTextureSize;
	int maxClipPlanes;
	int maxModelViewStacks;
	int maxProjectionStacks;
	int maxAttribStacks;
	int maxTextureStacks;
} t_gl_info;

void	count_vertices(t_obj_data *data);

void 		exit_error_with_message(const char *msg);

void		create_triangle(t_software_environ *env);
GLuint	load_shaders(t_software_environ *env);
void 		load_texture(t_software_environ *env);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void set_attribute(GLuint id_program, const char *attribute_name);


void prepare(t_software_environ *env);
void render(t_software_environ *env);

unsigned char	*load_bitmap_file(const char *pathname, size_t *width, size_t *height);

/*
** Math utils
*/

double	deg_to_rad(double deg);

/*
** Utils
*/
char	*ft_strjoin(char const *s1, char const *s2);

/*
** Logs
*/
bool	restart_gl_log();
bool	gl_log(const char* message, ...);
bool	gl_log_err(const char* message, ...);

#endif
