/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dissolved.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:24:25 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:24:26 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	read_dissolved(
		t_mtllib *lib,
		t_mtl_data *material,
		const t_token *tokens)
{
	(void)lib;
	material->dissolved = n_atof(tokens[0].cursor, tokens[0].size);
	if (material->dissolved < 0.f || material->dissolved > 1.f)
	{
		read_mtl_error("Invalid dissolved coefficient.");
		material->dissolved = 0.f;
	}
	return (0);
}
