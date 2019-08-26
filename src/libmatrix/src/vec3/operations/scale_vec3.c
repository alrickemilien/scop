/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:33:12 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:33:13 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vec3	scale_vec3(t_vec3 src, float factor)
{
	t_vec3 dest;

	dest.x = src.x * factor;
	dest.y = src.y * factor;
	dest.z = src.z * factor;
	return (dest);
}
