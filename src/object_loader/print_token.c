/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:08:47 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:08:48 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Debug function used to print tokens
*/

void	print_token(const t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].cursor)
	{
		printf("%s\n", tokens[i].cursor);
		i++;
	}
}
