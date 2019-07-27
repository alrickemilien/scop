/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_data_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 12:22:14 by aemilien          #+#    #+#             */
/*   Updated: 2018/12/15 12:23:14 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Gives data at the nth node of the list from the start
** When no nth noe, returns NULL
*/

void	*lst_data_at(t_list *list, size_t n)
{
	size_t	i;

	i = 0;
	while (list)
	{
		if (i == n)
			return (list->content);
		i++;
		list = list->next;
	}
	return (NULL);
}
