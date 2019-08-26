/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_vertices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:33:51 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:33:52 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	count_vertices(t_mesh *data)
{
	size_t	count;
	t_list	*x;

	x = data->polygons;
	count = 0;
	while (x)
	{
		count += ft_lstlen(((t_polygon*)x->content)->vertices);
		x = x->next;
	}
	data->vertex_count = count;
}
