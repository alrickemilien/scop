/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_normal_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:12:08 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:12:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

int			read_normal_vector(t_mesh *data, const t_token *tokens)
{
	t_vec3	normal;

	if (read_vec3(tokens, &normal) < 0)
		read_object_error("A normal needs three arguments.");
	ft_lstadd(&data->normals, ft_lstnew(&normal, sizeof(t_vec3)));
	return (0);
}
