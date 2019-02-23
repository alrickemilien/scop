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
				src/lib/load_shaders.c \
				src/lib/set_attribute.c \
				src/lib/math_utils.c \
				src/lib/load_texture.c \
				src/texture_loader/load_bitmap_file.c \
				src/lib/exit_error_with_msg.c \
				src/lib/count_vertices.c \
				src/lib/render.c \
				src/lib/prepare.c

SRC += src/controls/controls.c

SRC +=	src/object_loader/load_object_file.c \
				src/object_loader/load_object_file_utils.c \
				src/object_loader/read_color.c \
				src/object_loader/read_name.c \
				src/object_loader/read_mtl.c \
				src/object_loader/read_comment.c \
				src/object_loader/read_normal_vector.c \
				src/object_loader/read_object_file_line.c \
				src/object_loader/read_position.c \
				src/object_loader/read_face.c \
				src/object_loader/read_vec2.c \
				src/object_loader/read_vec3.c \
				src/object_loader/read_vertex.c \
				src/object_loader/read_object_error.c \
				src/object_loader/n_atof.c \
				src/object_loader/split_into_tokens.c

SRC += src/main.c


INCLUDE += -I include -I src/libft -I src/libvec/include -I src/libmatrix/include

LIBS += -lft -L src/libft -lmatrix -L src/libmatrix
