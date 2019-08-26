/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mat4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:59:56 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:59:57 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

/*
** Fill the matrix with the value past as parameter
*/

void	fill_mat4(t_mat4 *m, void *value)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		memcpy(&m->value[i], value, sizeof(GLfloat));
		i++;
	}
}
