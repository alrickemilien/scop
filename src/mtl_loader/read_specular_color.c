#include "material_template_library_loader.h"

int read_specular_color(
        t_mtllib *lib,
        t_mtl_data *material,
        const t_token *tokens)
{
    GLfloat c[3];
    size_t  i;

    (void)lib;
    memset(c, 0, sizeof(GLfloat) * 3);
    i = 0;
    while (tokens[i].cursor && i < 3)
    {
        c[i] = n_atof(tokens[0].cursor, tokens[0].size);
        i++;
    }

    while (tokens[i].cursor)
        i++;

    if (i != 3)
        read_mtl_error("Invalid specular color.");
    else
        material->specular = (t_vec3){c[0], c[1], c[2]};

    return (0);
}

int read_specular_color_exponent(
        t_mtllib *lib,
        t_mtl_data *material,
        const t_token *tokens)
{
    (void)lib;
    material->specular_exponent = n_atof(tokens[0].cursor, tokens[0].size);

    // Check exponent validity
    if (material->specular_exponent < 0 || material->specular_exponent > 1000)
    {
        read_mtl_error("Invalid specular color exponent.");
        material->specular_exponent = 0;
    }

    return (0);
}