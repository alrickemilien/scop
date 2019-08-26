/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_vec3_equal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:59:26 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:59:27 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

int	are_vec3_equal(
		const t_vec3 *vector1,
		const t_vec3 *vector2)
{
	if (memcmp(vector1, vector2, sizeof(t_vec3)))
		return (false);
	return (true);
}
