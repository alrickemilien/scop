/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmatrixutil_append_and_release_memory.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:56:57 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:56:58 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	libmatrixutil_append_and_release_memory(
		char **buffer,
		char *str)
{
	char	*new_buffer;
	size_t	buffer_len;
	size_t	str_len;

	if (*buffer == NULL)
	{
		*buffer = libmatrixutil_strdup(str);
		free(str);
		return ;
	}
	buffer_len = libmatrixutil_strlen(*buffer);
	str_len = libmatrixutil_strlen(str);
	new_buffer = (char*)malloc(sizeof(char) * (buffer_len + str_len + 1));
	if (!new_buffer)
		return ;
	libmatrixutil_memcpy(new_buffer, *buffer, buffer_len);
	libmatrixutil_memcpy(new_buffer + buffer_len, str, str_len);
	new_buffer[buffer_len + str_len] = 0;
	free(*buffer);
	free(str);
	*buffer = new_buffer;
}

/*
** Do not free the str parameter
** it is a static member that we must not touch
*/

void	libmatrixutil_append_and_release_memory_static(
		char **buffer,
		const char *str)
{
	char	*new_buffer;
	size_t	buffer_len;
	size_t	str_len;

	if (*buffer == NULL)
	{
		*buffer = libmatrixutil_strdup(str);
		return ;
	}
	buffer_len = libmatrixutil_strlen(*buffer);
	str_len = libmatrixutil_strlen(str);
	new_buffer = (char*)malloc(sizeof(char) * (buffer_len + str_len + 1));
	if (!new_buffer)
		return ;
	libmatrixutil_memcpy(new_buffer, *buffer, buffer_len);
	libmatrixutil_memcpy(new_buffer + buffer_len, str, str_len);
	new_buffer[buffer_len + str_len] = 0;
	free(*buffer);
	*buffer = new_buffer;
}
