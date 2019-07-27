#include "object_loader.h"

static bool		is_on_delimiter(const char *line, const char *delimiters)
{
	size_t	i;

	if (delimiters == NULL)
		return (false);
	i = 0;
	while (line[i] && delimiters[i])
	{
		if (line[i] != delimiters[i])
			return (false);
		i++;
	}
	if (!line[i] && delimiters[i])
		return (false);
	return (true);
}

/*
** Consider we are on a delimiter
*/

static size_t	skip_delimiters(const char *line, const char *delimiters)
{
	size_t	i;

	i = 0;
	while (delimiters[i] && line[i] == delimiters[i])
		i++;
	return (i);
}

// Get number of token
static size_t	count_words(const char *line, const char *delimiters)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (line[i])
	{
		// Skip whitespaces and non printable
		while (line[i] && !is_printable(line[i]))
			i++;
		if (is_on_delimiter(line + i, delimiters))
			i += skip_delimiters(line + i, delimiters);
		if (line[i] && !is_on_delimiter(line + i, delimiters))
			n++;
		while (line[i] && is_printable(line[i]) && !is_on_delimiter(line + i, delimiters))
			i++;
	}
	return (n);
}

t_token *split_into_tokens(const char *line, const char *delimiters)
{
	size_t	i;
	size_t	n;
	t_token	token;
	t_token	*array;

	if (NULL == line)
		return (NULL);
	n = count_words(line, delimiters);
	if (NULL == (array = (t_token*)malloc(sizeof(t_token) * (n + 1))))
		return (NULL);
	array[n] = (t_token){ 0, 0 };
	i = 0;
	n = 0;
	while(line[i])
	{
		// Skip whitespaces and non printable
		while (line[i] && !is_printable(line[i]))
			i++;
		if (is_on_delimiter(line + i, delimiters))
			i += skip_delimiters(line + i, delimiters);
		if (line[i] && !is_on_delimiter(line + i, delimiters))
		{
			token.cursor = (char*)((size_t)line + i);
			token.size = 0;
			while (line[i] && is_printable(line[i]) && !is_on_delimiter(line + i, delimiters))
			{
				token.size++;
				i++;
			}
			memcpy(&array[n], &token, sizeof(t_token));
			n++;
		}
	}
	return (array);
}
