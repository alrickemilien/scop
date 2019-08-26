/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_diffuse_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:22:39 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:22:42 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	read_diffuse_color(
		t_mtllib *lib,
		t_mtl_data *material,
		const t_token *tokens)
{
	GLfloat c[3];
	size_t	i;

	(void)lib;
	i = 0;
	memset(c, 0, sizeof(GLfloat) * 3);
	while (tokens[i].cursor && i < 3)
	{
		c[i] = n_atof(tokens[0].cursor, tokens[0].size);
		i++;
	}
	while (tokens[i].cursor)
		i++;
	if (i != 3)
		read_mtl_error("Invalid diffuse color.");
	else
		material->diffuse = (t_vec3){c[0], c[1], c[2]};
	return (0);
}
