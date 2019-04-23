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
SRC +=	../src/core/create_triangle.c \
				../src/core/load_shaders.c \
				../src/core/load_single_shader.c \
				../src/core/gl_attribute.c \
				../src/core/math_utils.c \
				../src/core/load_texture.c \
				../src/texture_loader/load_bitmap_file.c \
				../src/core/exit_error_with_msg.c \
				../src/core/count_vertices.c \
				../src/core/render.c \
				../src/core/gl_buffering.c \
				../src/core/gl_matrixing.c \
				../src/core/check_gl_error.c

#
# Controls and toggle of the app
#
SRC += ../src/controls/controls.c \
		../src/controls/keyboards.c

#
# .obj loader
#
SRC +=	../src/object_loader/load_object_file.c \
				../src/object_loader/read_color.c \
				../src/object_loader/read_name.c \
				../src/object_loader/read_mtl.c \
				../src/object_loader/read_comment.c \
				../src/object_loader/read_normal_vector.c \
				../src/object_loader/read_object_file_line.c \
				../src/object_loader/read_position.c \
				../src/object_loader/read_face.c \
				../src/object_loader/read_vec2.c \
				../src/object_loader/read_vec3.c \
				../src/object_loader/read_vertex.c \
				../src/object_loader/read_object_error.c \
				../src/object_loader/print_object.c \
				../src/object_loader/print_token.c

#
# Loader utils
#
SRC +=	../src/loader_utils/n_atof.c \
				../src/loader_utils/split_into_tokens.c \
				../src/loader_utils/utils.c

#
# .mtl loader
#
SRC +=	../src/mtl_loader/load_mtl_file.c \
				../src/mtl_loader/read_mtl_file_line.c \
				../src/mtl_loader/read_new_mtl.c \
				../src/mtl_loader/read_comment.c

#
# Logs
#
SRC += ../src/core/gl_log.c

#
# Utils
#
SRC +=	../src/utils/ft_lstadd.c \
		../src/utils/ft_lstdel.c\
		../src/utils/ft_lstdelone.c\
		../src/utils/ft_lstlen.c\
		../src/utils/ft_lstnew.c\
		../src/utils/ft_lstreverse.c\
		../src/utils/ft_strjoin.c\
		../src/utils/lst_data_at.c

SRC += ../src/main.c

INCLUDE += -I ../include -I ../src/libmatrix/include

LIBS += -lmatrix -L ../src/libmatrix