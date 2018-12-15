#include "object_loading.h"

int		parse_vec2(const t_token *tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 2))
		return (-1);

	// @TODO need check of values
	vector->x = atof(&tokens->cursor[0]);
	vector->y = atof(&tokens->cursor[1]);

	return (0);
}
