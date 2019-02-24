/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:54:45 by aemilien          #+#    #+#             */
/*   Updated: 2018/10/06 13:54:46 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstreverse(t_list **lst)
{
	t_list	*before;
	t_list	*current;

	if (!*lst || !(*lst)->next)
		return ;
	current = *lst;
	before = *lst;
	*lst = (*lst)->next;
	current->next = NULL;
	while ((*lst)->next)
	{
		current = *lst;
		*lst = (*lst)->next;
		current->next = before;
		before = current;
	}
	(*lst)->next = before;
}
