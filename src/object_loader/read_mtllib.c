#include "object_loader.h"

int				read_mtllib(t_mesh *data, const t_token *tokens)
{
    size_t      i;
    char        *tmp;
    t_mtllib    lib;

    memset(&lib, 0, sizeof(t_mtllib));

    i = 0;
    while (tokens[i].cursor != NULL)
    {
        tmp = strndup(tokens[i].cursor, tokens[i].size);

        if (tmp == NULL)
            return (-1);

        lib.path = tmp;

	    ft_lstadd(&data->mtllib, ft_lstnew(&lib, sizeof(t_mtllib)));
        
        i++;
    }

	return (0);
}
