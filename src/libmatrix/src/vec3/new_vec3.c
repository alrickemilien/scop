#include "libmatrix.h"

/**
 * Return allocated vec3
 */
t_vec3  *new_vec3(
    GLfloat x,
    GLfloat y,
    GLfloat z)
{
    t_vec3 *v;

    v = (t_vec3*)malloc(sizeof(t_vec3));

    v->x = x;
    v->y = y;
    v->z = z;

    return (v);
}