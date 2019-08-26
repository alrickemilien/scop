/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:04:08 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:04:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	check_tokens_number(const t_token *token, size_t size)
{
	size_t	i;

	i = 0;
	while (token[i].cursor)
		i++;
	if (i < size)
		return (false);
	return (true);
}

bool	is_printable(char c)
{
	if (c >= 1 && c <= 32 && c != 127)
		return (false);
	return (true);
}

int		token_to_int(const t_token *token, size_t index)
{
	size_t	j;
	int		ret;

	j = 0;
	while (j <= index)
	{
		if (!token[j++].cursor)
			return (-1);
	}
	ret = (int)n_atof(token[index].cursor, token[index].size);
	return (ret);
}
