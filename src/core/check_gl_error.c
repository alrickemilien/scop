#include "scop.h"

/*
** Provides gl error string message if any
*/

static const glmaperror_t	g_glmaperror[] = {
	{ GL_INVALID_OPERATION, "GL_INVALID_OPERATION", },
	{ GL_INVALID_ENUM, "GL_INVALID_ENUM", },
	{ GL_INVALID_VALUE, "GL_INVALID_VALUE", },
	{ GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY", },
	{ GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION", },
};

int							check_gl_error(void)
{
	GLenum	err;
	char	*error;
	size_t	i;

	error = 0;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		error = "Unhandled GL error";
		i = 0;
		while (i * sizeof(glmaperror_t) < sizeof(g_glmaperror))
		{
			if (g_glmaperror[i].err == err)
				error = g_glmaperror[i].string_error;
		}
#ifdef _MSC_VER
		fprintf(stderr, "[GL Error]: %s\n", error);
#else
		fprintf(stderr, isatty(fileno(stderr)) ? "\033[31m[GL Error]\033[0m : %s\n" : "[GL Error] : %s\n", error);
#endif
		return (-1);
	}
	return (0);
}
