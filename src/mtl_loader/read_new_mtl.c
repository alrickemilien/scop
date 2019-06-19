#include "material_template_library_loader.h"

int				read_new_mtl(t_mtllib *lib, t_mtl_data d, const t_token *tokens)
{
	t_mtl_data mtl;

	(void)d;

	memset(&mtl, 0, sizeof(t_mtl_data));

	mtl.label = strndup(tokens[0].cursor, tokens[0].size);

	ft_lstadd(&lib->materials_list,
		ft_lstnew(&mtl, sizeof(t_mtl_data)));

	return (0);
}
