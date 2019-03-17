ifndef SRC
	SRC :=
endif

ifndef INCLUDE
	INCLUDE :=
endif

ifndef LIBS
	LIBS :=
endif

#
# scop core functions library
#
SRC +=	src/lib/create_triangle.c \
				src/lib/load_shaders.c \
				src/lib/load_single_shader.c \
				src/lib/set_attribute.c \
				src/lib/math_utils.c \
				src/lib/load_texture.c \
				src/texture_loader/load_bitmap_file.c \
				src/lib/exit_error_with_msg.c \
				src/lib/count_vertices.c \
				src/lib/render.c \
				src/lib/prepare.c

#
# controls and toggle of the app
#
SRC += src/controls/controls.c

#
# .obj loader
#
SRC +=	src/object_loader/load_object_file.c \
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
				src/object_loader/print_object.c

#
# Loader utils
#
SRC +=	src/loader_utils/n_atof.c \
				src/loader_utils/split_into_tokens.c \
				src/loader_utils/utils.c

#
# .mtl loader
#
SRC +=	src/mtl_loader/load_mtl_file.c \
				src/mtl_loader/read_mtl_file_line.c \
				src/mtl_loader/read_new_mtl.c \
				src/mtl_loader/read_comment.c

#
# Logs
#
SRC += src/lib/gl_log.c

#
# utils
#
SRC +=	src/utils/ft_lstadd.c \
		src/utils/ft_lstdel.c\
		src/utils/ft_lstdelone.c\
		src/utils/ft_lstlen.c\
		src/utils/ft_lstnew.c\
		src/utils/ft_lstreverse.c\
		src/utils/ft_strjoin.c\
		src/utils/lst_data_at.c

SRC += src/main.c

INCLUDE += -I include -I src/libmatrix/include

LIBS += -lmatrix -L src/libmatrix
