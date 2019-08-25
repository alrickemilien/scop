#include "object_loader.h"

int	read_smooth_shading(t_mesh *data, const t_token *tokens)
{
	int		s;
	char	*off;

	s = n_atoi(tokens[0].cursor, tokens[0].size);
	if (s == 0 && tokens[0].size > 1)
	{
		if(!(off = strndup(tokens[0].cursor, tokens[0].size)))
            return (-1);
		data->smooth_shading = -1;
		if (memcmp(off, "off", sizeof(char) * 3) && tokens[0].size == 3)
			data->smooth_shading = -1;
		else
			read_object_error("Invalid smooth shading\n");
	}
	if (tokens[0].size != 0 && tokens[1].cursor != NULL)
		read_object_error("Invalid smooth shading\n");
	return (0);
}
