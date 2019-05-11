#include "libmatrix.h"

const float DEG2RAD = 3.141593f / 180.0f;

void	rotate_x_mat4(t_mat4 *m, GLfloat angle)
{
    GLfloat c = cosf(angle * DEG2RAD);
    GLfloat s = sinf(angle * DEG2RAD);

    m->value[1] = m->value[1] * c + m->value[2] *-s;
    m->value[2] = m->value[1] * s + m->value[2] * c;
    m->value[5] = m->value[5] * c + m->value[6] *-s;
    m->value[6] = m->value[5] * s + m->value[6] * c;
    m->value[9] = m->value[9] * c + m->value[10] *-s;
    m->value[10]= m->value[9] * s + m->value[10] * c;
    m->value[13]= m->value[13] * c + m->value[14] *-s;
    m->value[14]= m->value[13] * s + m->value[14] * c;
}

void	rotate_y_mat4(t_mat4 *m, GLfloat angle)
{
    GLfloat c = cosf(angle * DEG2RAD);
    GLfloat s = sinf(angle * DEG2RAD);

    m->value[0] = m->value[0] * c + m->value[2] * s;
    m->value[2] = m->value[0] *-s + m->value[2] * c;
    m->value[4] = m->value[4] * c + m->value[6] * s;
    m->value[6] = m->value[4] *-s + m->value[6] * c;
    m->value[8] = m->value[8] * c + m->value[10]* s;
    m->value[10]= m->value[8] *-s + m->value[10]* c;
    m->value[12]= m->value[12] * c + m->value[14]* s;
    m->value[14]= m->value[12] *-s + m->value[14]* c;
}

void	rotate_z_mat4(t_mat4 *m, GLfloat angle)
{
    GLfloat c = cosf(angle * DEG2RAD);
    GLfloat s = sinf(angle * DEG2RAD);

    m->value[0] = m->value[0] * c + m->value[1] *-s;
    m->value[1] = m->value[0] * s + m->value[1] * c;
    m->value[4] = m->value[4] * c + m->value[5] *-s;
    m->value[5] = m->value[4] * s + m->value[5] * c;
    m->value[8] = m->value[8] * c + m->value[9] *-s;
    m->value[9] = m->value[8] * s + m->value[9] * c;
    m->value[12]= m->value[12] * c + m->value[13] *-s;
    m->value[13]= m->value[12] * s + m->value[13] * c;
}