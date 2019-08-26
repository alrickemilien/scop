/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:12:33 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:12:34 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

int			read_position(t_mesh *data, const t_token *tokens)
{
	t_vec3	new_position;

	if (read_vec3(tokens, &new_position) < 0)
		return (-1);
	ft_lstadd(&data->positions, ft_lstnew(&new_position, sizeof(t_vec3)));
	return (0);
}
