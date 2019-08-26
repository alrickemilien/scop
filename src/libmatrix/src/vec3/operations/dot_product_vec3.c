/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product_vec3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:33:18 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:33:19 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

GLfloat	dot_product_vec3(const t_vec3 *vector1, const t_vec3 *vector2)
{
	return (vector1->x * vector2->x
				+ vector1->y * vector2->y
				+ vector1->z * vector2->z);
}
