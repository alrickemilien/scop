#ifndef VEC2_H
#define VEC2_H

/*
** Pragma for packing data, no byte padding for alignement 
*/

#pragma pack(push, 1)
typedef struct	s_vec2 {
	GLfloat		x;
	GLfloat		y;
}				t_vec2;
#pragma pack(pop)

t_vec2			*new_vec2(
    GLfloat x,
    GLfloat y);

GLfloat			dot_product_vec2(
	const t_vec2 *vector1,
	const t_vec2 *vector2);

int				are_vec2_equal(
	const t_vec2 *vector1,
	const t_vec2 *vector2);

void			copy_vec2(
	t_vec2 *dest,
	const t_vec2 *src);

void			normalize_vec2(
	t_vec2 *vector);

GLfloat			magnitude_vec2(
	const t_vec2 *vector);

void			add_vec2(
	t_vec2 *vector,
	const t_vec2 *modifier);

void			substract_vec2(
	t_vec2 *vector,
	const t_vec2 *modifier);

void			cross_vec2(
	t_vec2 *vector1,
	const t_vec2 *vector2);

void			set_vec2(
	t_vec2 *vector,
	GLfloat x,
	GLfloat y,
	GLfloat z);

# define __VEC2_ORIGIN__ __libvec__vec2_origin;
# define __VEC2_X__ __libvec__vec2_x;
# define __VEC2_X_MINUS__ __libvec__vec2_x_minus;
# define __VEC2_Y__ __libvec__vec2_y;
# define __VEC2_Y_MINUS__ __libvec__vec2_y_minus;
# define __VEC2_Z__ __libvec__vec2_z;
# define __VEC2_Z_MINUS__ __libvec__vec2_z_minus;

#endif