/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shader_program.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:26:03 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:26:08 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	cleanup_shader(
		shader_program_t *p,
		shader_t *s)
{
	if (!s)
		return ;
	glDetachShader(p->id, s->id);
	glDeleteShader(p->id);
	free(s->path);
	munmap(s->content, s->length);
	free(s);
}

void		cleanup_shader_program(
		shader_program_t *p)
{
	cleanup_shader(p, p->vertex_shader);
	cleanup_shader(p, p->fragment_shader);
	cleanup_shader(p, p->geometry_shader);
	glDeleteProgram(p->id);
}
