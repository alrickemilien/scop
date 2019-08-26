/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_to_mat4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:01:11 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:01:12 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static const float	g_degtorad = 3.141593f / 180.0f;

t_mat4				rotate_x_to_mat4(
		t_mat4 *src,
		t_mat4 *dest,
		GLfloat angle)
{
	GLfloat	alpha;

	memcpy(dest, src, sizeof(GLfloat) * 16);
	alpha = angle * g_degtorad;
	dest->value[5] = cosf(alpha);
	dest->value[6] = sinf(alpha);
	dest->value[9] = -sinf(alpha);
	dest->value[10] = cosf(alpha);
	return (*dest);
}

t_mat4				rotate_y_to_mat4(
		t_mat4 *src,
		t_mat4 *dest,
		GLfloat angle)
{
	GLfloat	alpha;

	memcpy(dest, src, sizeof(GLfloat) * 16);
	alpha = angle * g_degtorad;
	dest->value[0] = cosf(alpha);
	dest->value[2] = -sinf(alpha);
	dest->value[8] = sinf(alpha);
	dest->value[10] = cosf(alpha);
	return (*dest);
}

t_mat4				rotate_z_to_mat4(
		t_mat4 *src,
		t_mat4 *dest,
		GLfloat angle)
{
	GLfloat	alpha;

	memcpy(dest, src, sizeof(GLfloat) * 16);
	alpha = angle * g_degtorad;
	dest->value[0] = cosf(alpha);
	dest->value[1] = sinf(alpha);
	dest->value[4] = -sinf(alpha);
	dest->value[5] = cosf(alpha);
	return (*dest);
}
