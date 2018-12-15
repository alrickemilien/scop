ifndef SRC
	SRC :=
endif

ifndef INCLUDE
	INCLUDE :=
endif

ifndef LIBS
	LIBS :=
endif

SRC +=	src/lib/create_triangle.c \
				src/lib/load_shaders.c

SRC +=	src/object_loader/load_object_file.c \
				src/object_loader/load_object_file_utils.c \
				src/object_loader/read_color.c \
				src/object_loader/read_comment.c \
				src/object_loader/read_normal_vector.c \
				src/object_loader/read_object_file_line.c \
				src/object_loader/read_position.c \
				src/object_loader/read_poylgon.c \
				src/object_loader/read_vec2.c \
				src/object_loader/read_vec3.c \
				src/object_loader/read_vertex.c \
				src/object_loader/read_object_error.c \
				src/object_loader/split_into_tokens.c

SRC += src/main.c


INCLUDE += -I include -I src/libft -I src/libvec/include

LIBS += -lft -L src/libft
