ifndef SRC
	SRC :=
endif

ifndef INCLUDE
	INCLUDE :=
endif

SRC +=	src/are_vec_equal.c \
				src/constant.c \
				src/copy_vec.c \
				src/is_vec_origin.c \
				src/normalize_vec.c \
				src/operations/add_vec.c \
				src/operations/dot_product_vec.c \
				src/operations/magnitude_vec.c \
				src/operations/scale_vec.c \
				src/operations/substract_vec.c \
				src/set_vec.c \
				src/swap_vec.c

INCLUDE += -I include
