/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:14:22 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:14:28 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

/*
** @TODO need check of values
*/

int	parse_vec2(const t_token *tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 2))
		return (-1);
	vector->x = n_atof(tokens[0].cursor, tokens[0].size);
	vector->y = n_atof(tokens[1].cursor, tokens[1].size);
	return (0);
}
