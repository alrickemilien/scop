#include "object_loader.h"

/*
** Consider we are on a delimiter
*/

static size_t skip_delimiters(const char *line, const char *delimiters)
{
	size_t 		i;

	i = 0;
	while (delimiters[i] && line[i] == delimiters[i])
		i++;

	return (i);
}

// Get number of token
static size_t count_words(const char *line)
{
	size_t 		i;
	size_t 		n;

	i = 0;
	n = 0;
	while (line[i])
	{
		// Skip whitespaces and non printable
		while (line[i] && !is_printable(line[i]))
			i++;
		if (line[i])
			n++;
		while (line[i] && is_printable(line[i]))
			i++;
	}
	printf("split_whitespaces count_words return n %ld\n", n);

	return (n);
}

static t_token* bufferize(const char *line)
{
	size_t		n;
	t_token		*array;

    n = count_words(line);
	if (NULL == (array = (t_token*)malloc(sizeof(t_token) * (n + 1))))
		return (NULL);
	array[n] = (t_token){ 0, 0 };

    return (array);
}

t_token *split_whitespaces(const char *line)
{
	size_t		i;
	size_t		n;
	t_token		token;
	t_token		*array;

	if (NULL == line)
		return (NULL);
	array = bufferize(line);
	i = 0;
	n = 0;
	while(line[i])
	{
		// Skip whitespaces and non printable
		while (line[i] && !is_printable(line[i]))
			i++;
		if (line[i])
		{
			token.cursor = (char*)((size_t)line + i);
			token.size = 0;
			while (line[i] && is_printable(line[i]))
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
