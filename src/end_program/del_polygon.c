/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_polygon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:57:17 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:57:18 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Clear the environnement in memory
*/

void	del_polygon(void *p, size_t s)
{
	t_polygon	*polygon;

	(void)s;
	polygon = (t_polygon*)p;
	ft_lstdel(&polygon->vertices, &del_vertex);
	free(polygon);
}
