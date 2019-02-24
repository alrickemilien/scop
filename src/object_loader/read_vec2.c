#include "object_loader.h"

int		parse_vec2(const t_token *tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 2))
		return (-1);

	// @TODO need check of values
	vector->x = n_atof(tokens[0].cursor, tokens[0].size);
	vector->y = n_atof(tokens[1].cursor, tokens[1].size);

	return (0);
}
