#include "object_loader.h"
#include "utils.h"

static char    *build_mtllib_full_path(
    const char *object_file_path,
    const char *mtllib_filename)
{
    char    *ret;
    char    *tmp;

    tmp = extract_folder_from_path(object_file_path);

    ret = ft_strjoin(tmp, mtllib_filename);

    free(tmp);

    return (ret);
}

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

        printf("data->path : %s\n", data->path);

        lib.path = build_mtllib_full_path(data->path, tmp);

        printf("lib.path : %s\n", lib.path);

	    ft_lstadd(&data->mtllib, ft_lstnew(&lib, sizeof(t_mtllib)));

        free(tmp);
        
        i++;
    }

	return (0);
}
