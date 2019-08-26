/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_mat4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:00:53 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:00:54 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_mat4	translate_mat4(
		t_mat4 *dest,
		const t_vec3 *amount)
{
	dest->value[12] += amount->x;
	dest->value[13] += amount->y;
	dest->value[14] += amount->z;
	return (*dest);
}

t_mat4	translate_to_mat4(
		const t_mat4 *src,
		t_mat4 *dest,
		const t_vec3 *amount)
{
	memcpy(dest->value, src->value, 16 * sizeof(GLfloat));
	dest->value[12] += amount->x;
	dest->value[13] += amount->y;
	dest->value[14] += amount->z;
	return (*dest);
}
