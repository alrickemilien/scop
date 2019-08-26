/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:14:40 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:14:51 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

int	read_vec3(const t_token *tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 3))
	{
		printf("Invalid read of vector\n");
		return (0);
	}
	vector->x = n_atof(tokens[0].cursor, tokens[0].size);
	vector->y = n_atof(tokens[1].cursor, tokens[1].size);
	vector->z = n_atof(tokens[2].cursor, tokens[2].size);
	return (1);
}
