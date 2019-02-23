#include "object_loading.h"

int			read_position(t_obj_data *data, const t_token *tokens)
{
	t_vec3	new_position;

	printf("line ==> : %s\n", tokens[0].cursor);

	// DEBUG ==> compute ctokens length
	size_t i;
	for (i = 0; tokens[i].cursor; i++) {
		printf("tokens[i].cursor[0] : %c\n", tokens[i].cursor[0]);
	}

	printf("ctoken length : %ld\n", i);

	if (read_vec3(tokens, &new_position) < 0)
		return (0);

  ft_lstadd(&data->positions, ft_lstnew(&new_position, sizeof(t_vec3)));

  return (1);
}
