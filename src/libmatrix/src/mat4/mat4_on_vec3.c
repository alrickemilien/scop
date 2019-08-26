/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_on_vec3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:00:22 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:00:23 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vec3	mat4_on_vec3(t_vec3 *v, const t_mat4 *m)
{
	GLfloat	w;

	v->x = m->value[0] * v->x
		+ m->value[4] * v->y
		+ m->value[8] * v->z
		+ m->value[12];
	v->y = m->value[1] * v->x
		+ m->value[5] * v->y
		+ m->value[9] * v->z
		+ m->value[13];
	v->z = m->value[2] * v->x
		+ m->value[6] * v->y
		+ m->value[10] * v->z
		+ m->value[14];
	w = m->value[3] * v->x
		+ m->value[7] * v->y
		+ m->value[11] * v->z
		+ m->value[15];
	*v = (t_vec3){v->x / w, v->y / w, v->z / w};
	return (*v);
}

t_vec3	mat4_to_vec3(const t_vec3 *src, t_vec3 *dest, const t_mat4 *m)
{
	GLfloat	w;

	dest->x = m->value[0] * src->x
		+ m->value[4] * src->y
		+ m->value[8] * src->z
		+ m->value[12];
	dest->y = m->value[1] * src->x
		+ m->value[5] * src->y
		+ m->value[9] * src->z
		+ m->value[13];
	dest->z = m->value[2] * src->x
		+ m->value[6] * src->y
		+ m->value[10] * src->z
		+ m->value[14];
	w = m->value[3] * src->x
		+ m->value[7] * src->y
		+ m->value[11] * src->z
		+ m->value[15];
	*dest = (t_vec3){dest->x / w, dest->y / w, dest->z / w};
	return (*dest);
}
