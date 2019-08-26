/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:04:30 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:04:31 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

GLfloat	magnitude_vec3(const t_vec3 *vector)
{
	return (sqrtf(
				powf(vector->x, 2)
				+ powf(vector->y, 2)
				+ powf(vector->z, 2)));
}
