#include "object_loading.h"

bool			check_tokens_number(const char **tokens, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (!tokens[i++])
			return (false);
	}

	return (true);
}
