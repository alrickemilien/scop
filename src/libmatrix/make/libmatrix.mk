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
				../src/mat4/perspective_mat4.c \
				../src/mat4/rotate_mat4.c

SRC +=	../src/vec3/swap_vec3.c \
				../src/vec3/constant.c \
				../src/vec3/copy_vec3.c \
				../src/vec3/is_origin_vec3.c \
				../src/vec3/normalize_vec3.c \
				../src/vec3/set_vec3.c \
				../src/vec3/cross_vec3.c \
				../src/vec3/operations/scale_vec3.c \
				../src/vec3/operations/magnitude_vec3.c \
				../src/vec3/operations/dot_product_vec3.c \
				../src/vec3/operations/substract_vec3.c \
				../src/vec3/operations/add_vec3.c \
				../src/vec3/are_vec3_equal.c

SRC +=	../src/matrix/pmatrix.c \
				../src/matrix/determinant.c \
				../src/matrix/minor.c \
				../src/matrix/identity_matrix.c \
				../src/matrix/inverse_matrix.c \
				../src/matrix/compare_matrix.c \
				../src/matrix/add_matrix.c \
				../src/matrix/fill_matrix.c \
				../src/matrix/copy_matrix.c \
				../src/matrix/new_matrix.c \
				../src/matrix/new_matrix_from_raw.c \
				../src/matrix/delete_matrix.c \
				../src/matrix/matrix_at.c \
				../src/matrix/multiply_matrix_with_scalar.c \
				../src/matrix/multiply_matrix.c

INCLUDE += -I ../include
