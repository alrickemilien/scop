#ifndef LIBVEC_H
# define LIBVEC_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

static const t_vec3 __libvec__vec3_origin = { 0, 0, 0 };

static const t_vec3 __libvec__vec3_x = { 1, 0, 0 };
static const t_vec3 __libvec__vec3_x_minus = { -1, 0, 0 };

static const t_vec3 __libvec__vec3_y = { 0, 1, 0 };
static const t_vec3 __libvec__vec3_y_minus = { 0, -1, 0 };

static const t_vec3 __libvec__vec3_z = { 0, 0, 1 };
static const t_vec3 __libvec__vec3_z_minus = { 0, 0, -1 };

# define __VEC3_ORIGIN__ __libvec__vec3_origin;
# define __VEC3_X__ __libvec__vec3_x;
# define __VEC3_X_MINUS__ __libvec__vec3_x_minus;
# define __VEC3_Y__ __libvec__vec3_y;
# define __VEC3_Y_MINUS__ __libvec__vec3_y_minus;
# define __VEC3_Z__ __libvec__vec3_z;
# define __VEC3_Z_MINUS__ __libvec__vec3_z_minus;

/*
** Functionnalitys
*/

int				are_vec_equal(const t_vec3 *vector);

void			vec3_copy(t_vec3 *dest, const t_vec3 *src);

void			vec3_copy(t_vec3 *dest, const t_vec3 *src);

int				is_vec_origin(const t_vec3 *vector);

void			normalize_vec(t_vec3 *vector);

void			set_vec(t_vec3 *vector, float x, float y, float z);

void			swap_vec(t_vec3 **vector1, t_vec3 **vector2);

/*
** Operations
*/

float			dot_product_vec(const t_vec3 *vector1, const t_vec3 *vector2);

void			vec3_add(t_vec3 *vector, const t_vec3 *modifier);

void			substract_vec(t_vec3 *vector, const t_vec3 *modifier);

float			magnitude_vec(const t_vec3 *vector);

void			vec3_mult(t_vec3 *vector, float factor);

void			scale_vec(t_vec3 *vector, float factor);




#endif
