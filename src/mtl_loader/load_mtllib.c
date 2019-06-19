#include "material_template_library_loader.h"

int     load_mtllib(t_list *mtllib)
{
    printf("Load mtllibs ...\n");
    while (mtllib)
    {
        if (load_mtl_file(mtllib->content) < 0) {
            printf("Unable to load mtllib %s, exit.\n", ((t_mtllib*)mtllib->content)->path);
            return (-1);
        }

        mtllib = mtllib->next;
    }
    printf("Load mtllibs done ...\n");
	return (0);
}
