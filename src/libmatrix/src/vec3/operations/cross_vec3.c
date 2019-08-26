/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:58:49 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:58:50 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vec3	cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 dest;

	dest.x = a.y * b.z - a.z * b.y;
	dest.y = a.z * b.x - a.x * b.z;
	dest.z = a.x * b.y - a.y * b.x;
	return (dest);
}
