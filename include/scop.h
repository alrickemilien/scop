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

#ifdef _MSC_VER
# include <windows.h>
# endif

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

# include <io.h>
# include <direct.h>

#define _USE_MATH_DEFINES // for C
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

# include <math.h>
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
# include <math.h>

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
	char		*path;
}				shader_t;

typedef struct	shader_program_s {
	GLuint		id;
	char		*cwd;
	shader_t	*vertex_shader;
	shader_t	*fragment_shader;
	shader_t	*geometry_shader;
}				shader_program_t;

typedef struct	s_light
{
	t_vec3		position;
	t_vec3		color;
}				t_light;

/*
** Provides all maths parameters that are required
** to build view matrix
*/

typedef struct	s_camera {
				t_vec3 position;
				t_vec3 target;
				t_vec3 direction;
				t_vec3 up;
				t_vec3 right;
}				t_camera;

/*
** - The model matrix is a transformation matrix
**   that translates, scales and/or rotates your object to place it
**   in the world at a location/orientation they belong to.
**
** - The view space is the result of transforming your world-space coordinates
**   to coordinates that are in front of the user's view.
**   This is done through the view/lookAt matrix
**   The view space is thus the space as seen from the camera's point of view.
**
** - At the end of each vertex shader run,
**   OpenGL expects the coordinates to be within a specific range
**   and any coordinate that falls outside this range is clipped.
**   Coordinates that are clipped are discarded, so the remaining coordinates will end up as fragments visible on your screen.
**   This is also where clip space gets its name from.
**   The projection matrix then transforms coordinates within this specified range
**   to normalized device coordinates (-1.0, 1.0).
*/

typedef struct	s_software_environ
{
	int			window_width;
	int			window_height;
	GLFWwindow     *window;

	// Path to the current directory where the binary file ./scop is executed
	char 					cwd[PATH_MAX];

	// The data that will be flled during object file loading
	t_obj_data		data;
	t_light			light;

	// Scop options that can evolve during software run
	int			wireframe;
	int			auto_rotate;
	int			texturing;
	float		scale;

	GLfloat		ambient_lighting;
	GLfloat		specular_lighting;

	// Ligting
	GLuint		ambient_lighting_uni;
	GLuint		specular_lighting_uni;
	GLuint		light_uni;
	GLuint		eye_uni;

	t_vec3		camera_position;
	t_vec3		light_position;

	// render style value for glDrawArray()
	GLenum		render_style;

	GLfloat		y_auto_rotate_angle;

	const char	*path_to_texture;

	// OpenGL programs
	shader_program_t	object_shader_program;
	shader_program_t	internal_object_shader_program;
	shader_program_t	axis_shader_program;

	// OpenGL VAO and VBO
	GLuint 		vao;
	GLuint 		plan_vao;
	GLuint 		axis_vao;

	// INDEXATION MODE
	int			indexation_mode;
	GLuint		ebo;

	// Here we have a single VBO taht contains v/c/n
	GLuint		vbo;
	GLuint		plan_vbo;
	GLuint		axis_vbo;

	// OpenGL shaders variables
	GLuint		mvp_uni;
	GLuint		m_uni;
	GLuint		internal_object_mvp_uni;

	GLuint		texture_level;
	GLuint		light_color_uni;
	GLuint		texture_level_uni;
	GLuint		texture;

	t_mat4	*translation_matrix;
	t_mat4	*rotation_matrix;

	t_mat4	*model_matrix;
	t_mat4	*view_matrix;
	t_mat4	*projection_matrix;
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

void		count_vertices(t_obj_data *data);

void 		exit_error_with_message(const char *msg);

void		create_triangle(t_software_environ *env);

int 		load_program_shader(shader_program_t *env,
				const char *vertex_file_path,
				const char *fragment_file_path,
				const char *geometry_file_path);
int			load_single_shader(shader_t *shader, const char *path);
void		print_gl_shader_error(GLuint id, int info_log_length);
void		print_gl_program_error(GLuint id, int info_log_length);
void		cleanup_shader_program(shader_program_t *p);
int			compile_single_shader(shader_t *shader, int *info_log_length, GLint *result);

void 		load_texture(t_software_environ *env);

void		key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void		window_size_callback(GLFWwindow* window, int width, int height);

int			set_attribute(GLuint id_program, const char *attribute_name, size_t vertex_size);

int			check_gl_error(void);

void		smart_camera_position(
				t_software_environ *env,
				t_vec3 *camera_position,
				t_vec3 *camera_look_at_position,
				t_vec3 *camera_up);
void compute_vertex_normal(
				t_obj_data *mesh, 
				t_vertex* vertex, 
				t_vec3 *normal);

int			gl_buffering(t_software_environ *env);
int			gl_indexing(t_software_environ *env);
void		plan_to_vbo(t_software_environ *env);
void		axis_to_vbo(t_software_environ *env);
void		gl_matrixing(t_software_environ *env);
int			gl_lighting(t_software_environ *env);
void		render(t_software_environ *env);

unsigned char	*load_bitmap_file(const char *pathname, size_t *width, size_t *height);

/*
** Users inputs callbacks
*/
void			close_window_callback(t_software_environ *env, GLFWwindow* window);
void			scale_up(t_software_environ *env, GLFWwindow* window);
void			scale_down(t_software_environ *env, GLFWwindow* window);
void			switch_render_style(t_software_environ *env, GLFWwindow* window);
void			reduce_ambient_lighting(t_software_environ *env, GLFWwindow* window);
void			increase_ambient_lighting(t_software_environ *env, GLFWwindow* window);

/*
** Math utils
*/

double	deg_to_rad(double deg);
t_vec3	compute_object_barycentre(t_list *positions);

/*
** Utils
*/

char	*ft_strjoin(char const *s1, char const *s2);
#ifdef _MSC_VER
char	*strndup(char *str, int chars);
#endif

/*
** Logs
*/

bool	restart_gl_log();
bool	gl_log(const char* message, ...);
bool	gl_log_err(const char* message, ...);

#endif
