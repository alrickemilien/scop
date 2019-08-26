/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:04:16 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:04:17 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

static size_t	count_words(const char *line)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i] && !is_printable(line[i]))
			i++;
		if (line[i])
			n++;
		while (line[i] && is_printable(line[i]))
			i++;
	}
	return (n);
}

static t_token	*bufferize(const char *line)
{
	size_t	n;
	t_token	*array;

	n = count_words(line);
	if (NULL == (array = (t_token*)malloc(sizeof(t_token) * (n + 1))))
		return (NULL);
	array[n] = (t_token){ 0, 0 };
	return (array);
}

static size_t	on_whitespace(
	const char *line,
	t_token *array,
	size_t *n)
{
	size_t		i;
	t_token		token;

	token.cursor = (char*)(line);
	token.size = 0;
	i = 0;
	while (line[i] && is_printable(line[i]))
	{
		token.size++;
		i++;
	}
	memcpy(&array[*n], &token, sizeof(t_token));
	*n = *n + 1;
	return (i);
}

t_token			*split_whitespaces(
	const char *line)
{
	size_t		i;
	size_t		n;
	t_token		*array;

	if (NULL == line)
		return (NULL);
	array = bufferize(line);
	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i] && !is_printable(line[i]))
			i++;
		if (line[i])
			i += on_whitespace(line + i, array, &n);
	}
	return (array);
}
