#include "object_loading.h"

int		read_vec3(const char **tokens, t_vec3 *vector)
{
	if (!check_tokens_number(tokens, 3))
		return (0);

  // @TODO need check of values
  vector->x = atof(tokens[0]);
	vector->y = atof(tokens[1]);
	vector->z = atof(tokens[2]);

  return (1);
}
