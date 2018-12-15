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


inline bool is_printable(char c)
{
  if (c >= 1 && c <= 32)
    return (false);
  return (true);
}

int			token_to_int(const char **tokens, size_t index)
{
	size_t		j;
	int		ret;

	j = 0;
	while (j <= index)
	{
		if (!tokens[j++])
			return (DEFAULT_CODE);
	}
	ret = atoi(tokens[index]) - 1;
	if (ret < 0)
		read_object_error("A face index can't be negative.");
	return (ret);
}
