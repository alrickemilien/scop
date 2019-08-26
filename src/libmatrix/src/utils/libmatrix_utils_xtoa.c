/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmatrix_utils_xtoa.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:51:35 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:26:50 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

int					libmatrix_itoa(
		const void *param,
		char *buffer)
{
	int	value;

	libmatrixutil_memcpy(&value, param, sizeof(int));
	return ((int)itoa_hex(value, buffer, 10));
}

int					libmatrix_ltoa(
		const void *param,
		char *buffer)
{
	long	value;

	libmatrixutil_memcpy(&value, param, sizeof(long));
	return ((int)ltoa_hex(value, buffer, 10));
}

/*
** 2^-126 is the most little float you can have
** It is in decimal 2.3509887e-38
** It means that the most bigger number will be
** 1(The 2) +  1(The dot) +  38(e-38) + 1(\0 character) => 40 characters wide
*/

static int			libmatrix_ftoa_(
		const void *param,
		char *buffer,
		int precision_afterpoint)
{
	float	value;
	int		integer_part;
	float	float_part;
	size_t	i;
	char	g_integer_part_str[514];

	libmatrixutil_memcpy(&value, param, sizeof(float));
	libmatrixutil_bzero(buffer, sizeof(char) * 41);
	integer_part = (int)value;
	float_part = fabsf(value - (float)integer_part);
	i = itoa_hex(integer_part, g_integer_part_str, 10);
	libmatrixutil_memcpy(buffer, g_integer_part_str, i);
	buffer[i++] = '.';
	while (precision_afterpoint--)
	{
		float_part *= 10.0f;
		integer_part = float_part;
		buffer[i++] = '0' + integer_part;
		float_part -= integer_part;
	}
	while (buffer[i - 1] == '0' && buffer[i - 2] != '.')
		buffer[i-- - 1] = 0;
	return ((int)i);
}

/*
** 2^-126 is the most little float you can have
** It is in decimal 2.3509887e-38
** It means that the most bigger number will be
** 1(The 2) +  1(The dot) +  38(e-38) + 1(\0 character) => 40 characters wide
*/

int					libmatrix_ftoa(
		const void *param,
		char *buffer)
{
	return (libmatrix_ftoa_(param, buffer, 38));
}
