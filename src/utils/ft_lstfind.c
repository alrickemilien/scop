/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:53:20 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/25 17:53:23 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Return list node if list node's content fits
** into provided function
** or null if no one
*/

t_list	*ft_lstfind(t_list *root,
		const void *provided_content,
		bool (*f)(
			const void *node_content,
			const void *provided_content))
{
	while (root)
	{
		if (f(root->content, provided_content))
			return (root);
		root = root->next;
	}
	return (NULL);
}
