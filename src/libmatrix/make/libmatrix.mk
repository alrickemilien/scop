ifndef SRC
	SRC :=
endif

ifndef INCLUDE
	INCLUDE :=
endif

SRC +=	../src/utils/libmatrix_utils.c \
				../src/utils/libmatrix_stringutils.c \
				../src/utils/libmatrix_utils_xtoa.c

SRC +=	../src/mat4/mat4.c \
				../src/mat4/look_at_mat4.c \
				../src/mat4/look_at_mat4_2.c \
				../src/mat4/scale_mat4.c \
				../src/mat4/translate_mat4.c \
				../src/mat4/transpose_mat4.c \
				../src/mat4/perspective_mat4.c \
				../src/mat4/rotate_mat4.c \
				../src/mat4/mat4_on_vec3.c

SRC +=	../src/vec3/is_origin_vec3.c \
../src/vec3/swap_vec3.c \
../src/vec3/constant.c \
../src/vec3/copy_vec3.c \
../src/vec3/are_vec3_equal.c \
../src/vec3/normalize_vec3.c \
../src/vec3/set_vec3.c \
../src/vec3/magnitude_vec3.c \
../src/vec3/operations/magnitude_vec3.c \
../src/vec3/operations/cross_vec3.c \
../src/vec3/operations/return_sub_vec3.c \
../src/vec3/operations/scale_vec3.c \
../src/vec3/operations/add_vec3.c \
../src/vec3/operations/return_cross_vec3.c \
../src/vec3/operations/substract_vec3.c \
../src/vec3/operations/return_add_vec3.c \
../src/vec3/operations/dot_product_vec3.c

SRC +=	../src/mat4/pmatrix.c \
				../src/mat4/add_mat4.c \
				../src/mat4/fill_mat4.c \
				../src/mat4/delete_matrix.c \
				../src/mat4/multiply_mat4.c

INCLUDE += -I ../include
