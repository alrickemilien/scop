/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_vertex_same.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:37:54 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:37:54 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			is_vertex_same(
		const void *a,
		const void *b)
{
	t_vertex	*va;
	t_vertex	*vb;

	va = (t_vertex*)a;
	vb = (t_vertex*)b;
	if (va->position_index == vb->position_index
		&& va->normal_index == vb->normal_index)
		return (true);
	return (false);
}
