/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:18:43 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:18:44 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

void		print_vec3(void *data)
{
	t_vec3		*pos;

	pos = (t_vec3 *)data;
	printf(
		"\tx = %lf\n"
		"\ty = %lf\n"
		"\tz = %lf\n\n",
		pos->x,
		pos->y,
		pos->z);
}

void		print_vec2(void *data)
{
	t_vec2		*pos;

	pos = (t_vec2 *)data;
	printf("\tx = %lf\n"
			"\ty = %lf\n\n",
			pos->x, pos->y);
}
