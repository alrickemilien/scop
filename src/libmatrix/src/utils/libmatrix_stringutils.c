/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmatrix_stringutils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:57:10 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:57:13 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

size_t	libmatrixutil_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*libmatrixutil_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	return ((char*)libmatrixutil_memchr(
				(void*)s, c, libmatrixutil_strlen(s) + 1));
}

char	*libmatrixutil_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new;

	len = n;
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	new[len] = 0;
	return ((char *)libmatrixutil_memcpy(new, s, len));
}

char	*libmatrixutil_strdup(const char *s)
{
	size_t	len;
	char	*new;

	len = libmatrixutil_strlen(s);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	new[len] = 0;
	return ((char *)libmatrixutil_memcpy(new, s, len));
}
