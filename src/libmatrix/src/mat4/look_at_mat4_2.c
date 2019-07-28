#include "libmatrix.h"

/*
** Fill vec4 with row i of mat4
*/
void	mat4_row(t_vec4 *v, t_mat4 *matrix, size_t i)
{
	size_t	k;
	GLfloat	*r;

	r = (GLfloat*)v;
	while (k < 4)
	{
		r[k] = matrix->value[3 * i + k];		
		k++;
	}
}

GLfloat	vec4_mul_inner(t_vec4 v1, t_vec4 v2)
{
    size_t	i;
    GLfloat	p;
	GLfloat	*a;
	GLfloat	*b;

	a = (GLfloat*)&v1;
	b = (GLfloat*)&v2;
    p = 0.f;
	while (i < 4)
	{
		p += b[i] * a[i];
		i++;
	}
    return (p);
}

void	mat4_translate_in_place(t_mat4 *matrix, GLfloat x, GLfloat y, GLfloat z)
{
	size_t i;
	t_vec4 r;
	t_vec4 t;	
	
	t = (t_vec4){x, y, z, 0};
	i = 0;
	while (i < 4)
	{
		mat4_row(&r, matrix, i);
		matrix->value[3 * i + 3] += vec4_mul_inner(r, t);
		i++;
	}
}

/* Adapted from Android's OpenGL Matrix.java.                        
** See the OpenGL GLUT documentation for gluLookAt for a description 
** of the algorithm. We implement it in a straightforward way:       
** TODO: The negation of of can be spared by swapping the order of
**       operands in the following cross products in the right way.
*/

t_mat4	*look_at_mat4_2(const t_vec3 *eye, const t_vec3 *center, const t_vec3 *up_dir)
{

	t_vec3	forward;
	t_vec3	left;
	t_vec3	up;
	t_mat4	*matrix;

	matrix = new_mat4();

	copy_vec3(&forward, center);
	substract_vec3(&forward, eye);
	normalize_vec3(&forward);

	copy_vec3(&left, &forward);
	cross_vec3(&left, up_dir);
	normalize_vec3(&left);

	copy_vec3(&up, &left);
	cross_vec3(&up, &forward);

	memset(matrix->value, 0, sizeof(float) * 4 * 4);

	matrix->value[0] =  left.x;
	matrix->value[1] =  up.x;
	matrix->value[2] = forward.x;

	matrix->value[4] =  left.y;
	matrix->value[5] =  up.y;
	matrix->value[6] = forward.y;

	matrix->value[8] =  left.z;
	matrix->value[9] =  up.z;
	matrix->value[10] = forward.z;

	matrix->value[15] =  1.f;

	matrix->value[12] = -dot_product_vec3(&left, eye);
	matrix->value[13] = -dot_product_vec3(&up, eye);
	matrix->value[14] = dot_product_vec3(&forward, eye);

	return (matrix);
}