#include "object_loader.h"

/*
** @TODO need check of values
*/

int	read_vec3(const t_token *tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 3))
	{
		printf("Invalid read of vector\n");
		return (0);
	}
	vector->x = n_atof(tokens[0].cursor, tokens[0].size);
	vector->y = n_atof(tokens[1].cursor, tokens[1].size);
	vector->z = n_atof(tokens[2].cursor, tokens[2].size);
	return (1);
}
