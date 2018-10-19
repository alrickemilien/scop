#ifndef SCOP_H
#define SCOP_H

/*
* * OPENGL INCLUDES
*/
#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Windowing
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
// Windowing
#include <GLFW/glfw3.h>
#endif

#ifdef _MSC_VER
#include <windows.h>
#endif

/*
** LOCALS INCLUDES
*/

#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** MACROS to access more easily to x server pointeurs to variables
** that will be always manipulated
** like x_server, window, image_buffer, etc
*/
#define WINDOW env->window
#define WINDOW_WIDTH env->window_width
#define WINDOW_HEIGHT env->window_height

typedef struct	s_software_environ
{
	int			window_width;
	int			window_height;
	GLFWwindow     *window;
} t_software_environ;


typedef struct	s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
} t_color;

#define DEFAULT_WINDOW_WIDTH 600
#define DEFAULT_WINDOW_HEIGHT 600

/*
* * This structure groups all available variables linked to gl infos
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

void	gl_info(void);
void	create_triangle(t_software_environ *env);
GLuint	load_shaders(void);

#endif