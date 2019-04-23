#include "libmatrix.h"

t_mat4 *new_mat4()
{
    return (t_mat4*)new_matrix(4, 4);
}

t_mat4 *identity_mat4()
{
    return (t_mat4*)identity_matrix(4, 4);
}