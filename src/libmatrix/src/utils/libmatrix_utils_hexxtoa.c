/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmatrix_utils_hexxtoa.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:53:42 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:53:43 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static int	return_zero(char *str, int i)
{
	str[i++] = '0';
	str[i] = '\0';
	return (i);
}

int			itoa_hex(
		uint64_t value,
		char *str,
		uint64_t base)
{
	bool	is_negative;
	int		i;
	int		rem;

	libmatrixutil_bzero(str, 514 * sizeof(char));
	is_negative = false;
	i = 0;
	if (value == 0)
		return (return_zero(str, i));
	if ((int)value < 0 && base == 10)
	{
		is_negative = true;
		value = -value;
	}
	while (value != 0)
	{
		rem = value % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		value = value / base;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = 0;
	libmatrixutil_reverse_string(str, i);
	return (i);
}

int			ltoa_hex(
		uint64_t value,
		char *str,
		uint64_t base)
{
	bool	is_negative;
	int		i;
	long	rem;

	is_negative = false;
	i = 0;
	if (value == 0)
		return (return_zero(str, i));
	if ((long)value < 0 && base == 10)
	{
		is_negative = true;
		value = -value;
	}
	while (value != 0)
	{
		rem = value % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		value = value / base;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = 0;
	libmatrixutil_reverse_string(str, i);
	return (i);
}
