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
SRC += ../src/core/render.c \
../src/core/smart_camera_position.c \
../src/core/gl_lighting.c \
../src/core/gl_attribute.c \
../src/core/create_triangle.c \
../src/core/gl_buffering.c \
../src/core/check_gl_error.c \
../src/core/gl_log.c \
../src/core/exit_error_with_msg.c \
../src/core/gl_matrixing.c \
../src/core/count_vertices.c \
../src/core/compute_vertex_normal.c \
../src/core/compute_mvp.c \
../src/core/math_utils.c \
../src/core/gl_indexing.c \
../src/core/gl_texturing.c \
	../src/shader/print_shader_error.c \
	../src/shader/load_single_shader.c \
	../src/shader/load_program_shader.c \
	../src/shader/cleanup_shader_program.c \
	../src/shader/compile_shader.c \
	../src/texture_loader/bmp/load_bitmap_file.c \
	../src/core/compute_vertex_uvs.c

#
# TGA files
#
SRC += ../src/texture_loader/tga/load_tga_file.c \
../src/texture_loader/tga/utils.c \
../src/texture_loader/tga/decode_tga.c \
../src/texture_loader/load_texture_file.c

#
# Controls and toggle of the app
#
SRC += ../src/controls/resize.c \
		../src/controls/controls.c \
		../src/controls/keyboards.c

#
# .obj loader
#
SRC +=	../src/object_loader/read_position.c \
../src/object_loader/read_comment.c \
../src/object_loader/read_smooth_shading.c \
../src/object_loader/read_uv.c \
../src/object_loader/print_token.c \
../src/object_loader/read_object_file_line.c \
../src/object_loader/read_vertex.c \
../src/object_loader/read_mtllib.c \
../src/object_loader/read_vec2.c \
../src/object_loader/read_vec3.c \
../src/object_loader/read_normal_vector.c \
../src/object_loader/read_name.c \
../src/object_loader/load_object_file.c \
../src/object_loader/print_object.c \
../src/object_loader/read_usemtl.c \
../src/object_loader/read_object_error.c \
../src/object_loader/read_face.c


#
# .mtl loader
#
SRC += ../src/mtl_loader/read_mtl_error.c \
../src/mtl_loader/read_dissolved.c \
../src/mtl_loader/read_specular_color.c \
../src/mtl_loader/load_mtl_file.c \
../src/mtl_loader/read_illumination.c \
../src/mtl_loader/read_mtl_file_line.c \
../src/mtl_loader/read_comment.c \
../src/mtl_loader/read_ambient_color.c \
../src/mtl_loader/read_diffuse_color.c \
../src/mtl_loader/read_optical_density.c \
../src/mtl_loader/read_transparency.c \
../src/mtl_loader/read_new_mtl.c \
../src/mtl_loader/load_mtllib.c \
../src/mtl_loader/load_mtl_file.c \
				../src/mtl_loader/read_mtl_file_line.c \
				../src/mtl_loader/read_new_mtl.c \
				../src/mtl_loader/read_comment.c

#
# Loader utils
#
SRC +=	../src/loader_utils/utils.c \
../src/loader_utils/split_whitespaces.c \
../src/loader_utils/n_atof.c \
../src/loader_utils/split_into_tokens.c \
../src/loader_utils/n_atoi.c

#
# Logs
#
SRC += ../src/core/gl_log.c

#
# Utils
#
SRC +=	../src/utils/ft_strjoin.c \
		../src/utils/ft_lstindex.c \
		../src/utils/ft_lstadd.c \
		../src/utils/lst_data_at.c \
		../src/utils/ft_lstlen.c \
		../src/utils/ft_lstnew.c \
		../src/utils/ft_lstdel.c \
		../src/utils/ft_lstreverse.c \
		../src/utils/ft_lstdelone.c \
		../src/utils/ft_lstfind.c \
		../src/utils/extract_folder_from_path.c

SRC += ../src/main.c \
		../src/glfw_init.c \
		../src/system_init.c \
		../src/end_program.c

INCLUDE += -I ../include -I ../src/libmatrix/include

LIBS += -lmatrix -L ../src/libmatrix
