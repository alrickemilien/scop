/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_shader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:26:14 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:26:16 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	compile_single_shader(
		t_shader *shader,
		int *info_log_length,
		GLint *result)
{
	glShaderSource(shader->id, 1,
			(const GLchar *const*)(&shader->content), &shader->length);
	glCompileShader(shader->id);
	glGetShaderiv(shader->id, GL_COMPILE_STATUS, result);
	glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, info_log_length);
	if (*result == GL_FALSE)
	{
		print_gl_shader_error(shader->id, *info_log_length);
		return (-1);
	}
	return (0);
}
