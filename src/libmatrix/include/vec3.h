#ifndef VEC3_H
# define VEC3_H

/*
** Pragma for packing data, no byte padding for alignement
*/

# pragma pack(push, 1)

typedef struct  s_vec3 {
	GLfloat     x;
	GLfloat     y;
	GLfloat     z;
}               t_vec3;

# pragma pack(pop)

GLfloat			dot_product_vec3(
    const t_vec3 *vector1,
    const t_vec3 *vector2);

int				are_vec3_equal(
    const t_vec3 *vector1,
    const t_vec3 *vector2);

t_vec3			copy_vec3(
    t_vec3 *dest,
    const t_vec3 *src);

t_vec3			normalize_vec3(
		t_vec3 vector);

GLfloat			magnitude_vec3(
    const t_vec3 *vector);

t_vec3			add_vec3(
		t_vec3 vector, t_vec3 modifier);
t_vec3			sub_vec3(
		t_vec3 vector, t_vec3 modifier);
t_vec3			scale_vec3(
		t_vec3 vector, float factor);
t_vec3			cross_vec3(
		t_vec3 vector1, t_vec3 vector2);

t_vec3			set_vec3(
    t_vec3 *vector,
    GLfloat x,
    GLfloat y,
    GLfloat z);

# define __VEC3_ORIGIN__ __libvec__vec3_origin;
# define __VEC3_X__ __libvec__vec3_x;
# define __VEC3_X_MINUS__ __libvec__vec3_x_minus;
# define __VEC3_Y__ __libvec__vec3_y;
# define __VEC3_Y_MINUS__ __libvec__vec3_y_minus;
# define __VEC3_Z__ __libvec__vec3_z;
# define __VEC3_Z_MINUS__ __libvec__vec3_z_minus;

#endif
