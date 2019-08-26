/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:25:02 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:25:04 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	read_transparency(
		t_mtllib *lib,
		t_mtl_data *material,
		const t_token *tokens)
{
	(void)lib;
	material->transparency = n_atof(tokens[0].cursor, tokens[0].size);
	return (0);
}
