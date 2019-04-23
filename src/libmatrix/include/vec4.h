#ifndef VEC4_H
#define VEC4_H

/*
** Pragma for packing data, no byte padding for alignement 
*/

#pragma pack(push, 1)
typedef struct	s_vec4 {
	GLfloat				x;
	GLfloat				y;
	GLfloat				z;
	GLfloat				w;
}								t_vec4;
#pragma pack(pop)

GLfloat		dot_product_vec4(const t_vec4 *vector1, const t_vec4 *vector2);

int				are_vec4_equal(const t_vec4 *vector1, const t_vec4 *vector2);

void			copy_vec4(t_vec4 *dest, const t_vec4 *src);

void			normalize_vec4(t_vec4 *vector);

GLfloat		magnitude_vec4(const t_vec4 *vector);

void			add_vec4(t_vec4 *vector, const t_vec4 *modifier);

void			substract_vec4(t_vec4 *vector, const t_vec4 *modifier);

void			cross_vec4(t_vec4 *vector1, const t_vec4 *vector2);

void			set_vec4(t_vec4 *vector, GLfloat x, GLfloat y, GLfloat z);

# define __VEC4_ORIGIN__ __libvec__vec4_origin;
# define __VEC4_X__ __libvec__vec4_x;
# define __VEC4_X_MINUS__ __libvec__vec4_x_minus;
# define __VEC4_Y__ __libvec__vec4_y;
# define __VEC4_Y_MINUS__ __libvec__vec4_y_minus;
# define __VEC4_Z__ __libvec__vec4_z;
# define __VEC4_Z_MINUS__ __libvec__vec4_z_minus;

#endif