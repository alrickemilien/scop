/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:32:45 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:32:46 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vec3	add_vec3(t_vec3 vector, t_vec3 modifier)
{
	t_vec3 dest;

	dest.x = vector.x + modifier.x;
	dest.y = vector.y + modifier.y;
	dest.z = vector.z + modifier.z;
	return (dest);
}
