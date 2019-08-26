/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_atof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:03:50 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:03:51 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"
#include <math.h>

static float	is_negative(const char *str)
{
	float	negate;

	negate = 1;
	if (str[0] == '-')
		negate = -1;
	return (negate);
}

/*
** Convert string of size n into float
*/

float			n_atof(const char *str, size_t size)
{
	float	ret;
	float	negate;
	int		point_seen;
	int		i;
	int		digit;

	ret = 0;
	if ((negate = is_negative(str)) == -1)
		str++;
	i = 0;
	point_seen = -1;
	while (i < (int)size && str[i])
	{
		if (str[i] == '.')
			point_seen = i++;
		digit = str[i] - '0';
		if (!str[i] || digit < 0 || digit > 9)
			break ;
		if (point_seen > -1)
			ret += powf(0.1f, (float)(i - point_seen)) * (float)digit;
		else
			ret = ret * 10.0f + (float)digit;
		i++;
	}
	return (ret * negate);
}
