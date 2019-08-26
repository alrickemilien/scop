/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:57:05 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:57:07 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Clear the environnement in memory
*/

void	del_vertex(void *p, size_t s)
{
	t_vertex	*vertex;

	(void)s;
	vertex = (t_vertex*)p;
	free(vertex);
}
