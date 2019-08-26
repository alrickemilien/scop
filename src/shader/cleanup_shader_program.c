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
		t_shader_program *p,
		t_shader *s)
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
		t_shader_program *p)
{
	cleanup_shader(p, p->vertex_shader);
	cleanup_shader(p, p->fragment_shader);
	cleanup_shader(p, p->geometry_shader);
	glDeleteProgram(p->id);
}
