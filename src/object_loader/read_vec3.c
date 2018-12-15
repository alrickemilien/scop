#include "object_loading.h"

int		read_vec3(const t_token *tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 3))
		return (0);

  // @TODO need check of values
  vector->x = atof(&tokens->cursor[0]);
	vector->y = atof(&tokens->cursor[1]);
	vector->z = atof(&tokens->cursor[2]);

  return (1);
}
