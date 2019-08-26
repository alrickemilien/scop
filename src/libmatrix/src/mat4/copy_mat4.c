/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_mat4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:59:50 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:59:50 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_mat4	copy_mat4(t_mat4 *src, t_mat4 *destination)
{
	memcpy(destination->value, src->value, 16 * sizeof(GLfloat));
	return (*destination);
}
