/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:12:00 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:12:01 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

int	read_name(t_mesh *data, const t_token *tokens)
{
	if (data->name != NULL)
		return (read_object_error("The object has multiple name."));
	data->name = strndup(tokens[0].cursor, tokens[0].size);
	return (0);
}
