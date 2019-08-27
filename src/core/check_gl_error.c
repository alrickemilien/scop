/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gl_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:34:54 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/27 19:29:31 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Provides gl error string message if any
*/

static const t_glmaperror	g_glmaperror[] = {
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
		while (i * sizeof(t_glmaperror) < sizeof(g_glmaperror))
		{
			if (g_glmaperror[i].err == err)
				error = g_glmaperror[i].string_error;
			i++;
		}
		fprintf(stderr, isatty(fileno(stderr))
			? "\033[31m[GL Error]\033[0m : %s\n" : "[GL Error] : %s\n", error);
		return (-1);
	}
	return (0);
}
