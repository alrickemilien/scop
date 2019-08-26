/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_new_mtl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:24:53 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:24:54 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	read_new_mtl(t_mtllib *lib,
		t_mtl_data *material,
		const t_token *tokens)
{
	t_mtl_data	mtl;

	(void)material;
	memset(&mtl, 0, sizeof(t_mtl_data));
	mtl.label = strndup(tokens[0].cursor, tokens[0].size);
	ft_lstadd(&lib->materials_list,
			ft_lstnew(&mtl, sizeof(t_mtl_data)));
	return (0);
}
