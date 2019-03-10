# CMake version
cmake_minimum_required (VERSION 3.0)

# OPENGL package
FIND_PACKAGE(OpenGL REQUIRED)

# Sets the src directory
SET ( CMAKE_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Compile external dependencies
add_subdirectory (external/glfw)

add_subdirectory (external/glew)

add_subdirectory (src/libmatrix)

# Includes directory (-I on Makefile)
include_directories(
	external/glfw/include/GLFW/

	external/glew/include/

	include/

	src/libmatrix/include/
)

# Library to use (-l on Makefile)
set(ALL_LIBS
	${OPENGL_LIBRARY}

	glfw

	external/glew/lib/Debug/glewd

	src/libmatrix
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Create the executable
ADD_EXECUTABLE(scop
	src/lib/create_triangle.c
	src/lib/exit_error_with_msg.c
	src/lib/render.c
	src/lib/set_attribute.c
	src/lib/count_vertices.c
	src/lib/load_shaders.c
	src/lib/math_utils.c
	src/lib/prepare.c
	src/lib/load_texture.c

	src/object_loader/read_position.c
	src/object_loader/read_mtl.c
	src/object_loader/read_comment.c
	src/object_loader/read_color.c
	src/object_loader/read_object_file_line.c
	src/object_loader/read_vertex.c
	src/object_loader/read_vec2.c
	src/object_loader/read_vec3.c
	src/object_loader/load_object_file_utils.c
	src/object_loader/read_normal_vector.c
	src/object_loader/read_name.c
	src/object_loader/load_object_file.c
	src/object_loader/read_object_error.c
	src/object_loader/read_face.c

	src/loader_utils/n_atof.c
	src/loader_utils/split_into_tokens.c
	src/loader_utils/utils.c

	src/texture_loader/load_bitmap_file.c

	src/mtl_loader/load_mtl_file.c
	src/mtl_loader/read_mtl_file_line.c
	src/mtl_loader/read_comment.c
	src/mtl_loader/read_new_mtl.c

	src/controls/controls.c
	src/controls/toggles.c

	src/utils/ft_lstadd.c
	src/utils/ft_lstdel.c
	src/utils/ft_lstdelone.c
	src/utils/ft_lstlen.c
	src/utils/ft_lstnew.c
	src/utils/ft_lstreverse.c
	src/utils/ft_strjoin.c
	src/utils/lst_data_at.c

	src/lib/gl_log.c

	src/main.c

	shaders/SimpleVertexShader.glsl
	shaders/SimpleFragmentShader.glsl
)

TARGET_LINK_LIBRARIES(scop ${ALL_LIBS})

# Xcode and Visual working directories
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
