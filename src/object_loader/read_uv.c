/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:13:57 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:14:12 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

int	read_uv(t_mesh *data, const t_token *token)
{
	t_vec2	uv;

	if (!check_tokens_number(token, 2))
		read_object_error("A texture needs two arguments.");
	uv.x = (float)atof(&token->cursor[0]);
	uv.y = (float)atof(&token->cursor[1]);
	ft_lstadd(&data->uvs, ft_lstnew(&uv, sizeof(t_vec2)));
	return (0);
}
