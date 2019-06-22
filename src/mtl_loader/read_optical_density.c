#include "material_template_library_loader.h"

int read_optical_density(
        t_mtllib *lib,
        t_mtl_data *material,
        const t_token *tokens)
{
    (void)lib;
    material->optical_density = n_atof(tokens[0].cursor, tokens[0].size);

    return (0);
}