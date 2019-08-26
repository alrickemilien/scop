/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:59:13 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:59:14 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vec3	normalize_vec3(t_vec3 vector)
{
	float	magnitude;
	t_vec3	dest;

	magnitude = magnitude_vec3(&vector);
	dest = (t_vec3){
		vector.x / magnitude,
			vector.y / magnitude,
			vector.z / magnitude,
	};
	return (dest);
}
