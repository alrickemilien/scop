/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_texturing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:31:12 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:38:10 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Load a texture into OpenGL soft
*/

int	gl_texturing(t_software_environ *env)
{
	env->grey_scale_uni = glGetUniformLocation(
		env->object_shader_program.id, "grey_scale");
	if (!env->texture.is_texture_loaded)
		return (0);
	glGenTextures(1, &env->texture_id);
	check_gl_error();
	glActiveTexture(GL_TEXTURE0);
	check_gl_error();
	glBindTexture(GL_TEXTURE_2D, env->texture_id);
	check_gl_error();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			env->texture.width, env->texture.height,
			0, env->texture.format,
			GL_UNSIGNED_BYTE, env->texture.data);
	check_gl_error();
	env->texture_uni = glGetUniformLocation(
			env->object_shader_program.id, "texture_sample");
	check_gl_error();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	check_gl_error();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	check_gl_error();
	return (0);
}
