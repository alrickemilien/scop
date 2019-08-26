/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:59:05 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:59:06 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

/*
** Return allocated vec2
*/

t_vec2	*new_vec2(
		GLfloat x,
		GLfloat y)
{
	t_vec2	*v;

	v = (t_vec2*)malloc(sizeof(t_vec2));
	v->x = x;
	v->y = y;
	return (v);
}
