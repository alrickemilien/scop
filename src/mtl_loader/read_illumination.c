/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_illumination.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:22:08 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:22:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	read_illumination(
		t_mtllib *lib,
		t_mtl_data *material,
		const t_token *tokens)
{
	(void)lib;
	material->illumination = n_atof(tokens[0].cursor, tokens[0].size);
	if (material->illumination < 0.f)
	{
		read_mtl_error("Invalid illumination coefficient.");
		material->illumination = 0.f;
	}
	return (0);
}
