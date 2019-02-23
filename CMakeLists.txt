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

# Create distrib subdirectory
if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

# Includes directory (-I on Makefile)
include_directories(
	external/glfw/include/GLFW/

	external/glew/include/

	include/

	src/libft/

	src/libmatrix/include/
)

# Libft
add_custom_target(
   libft
   COMMAND make
   WORKING_DIRECTORY src/libft
)

# Libmatrix
add_custom_target(
   libmatrix
   COMMAND make
   WORKING_DIRECTORY src/libmatrix
)

# Library to use (-l on Makefile)
set(ALL_LIBS
	${OPENGL_LIBRARY}

	glfw

	GLEW_1130

	src/libft

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
	src/main.c

	src/lib/create_triangle.c
	src/lib/load_shaders.c
	src/lib/set_attribute.c
	src/lib/math_utils.c
	src/lib/load_texture.c
	src/texture_loader/load_bitmap_file.c
	src/lib/prepare.c
	src/lib/exit_error_with_msg.c

	src/controls/controls.c

	src/object_loader/load_object_file.c
	src/object_loader/load_object_file_utils.c
	src/object_loader/read_color.c
	src/object_loader/read_comment.c
	src/object_loader/read_normal_vector.c
	src/object_loader/read_object_file_line.c
	src/object_loader/read_position.c
	src/object_loader/read_poylgon.c
	src/object_loader/read_vec2.c
	src/object_loader/read_vec3.c
	src/object_loader/read_vertex.c
	src/object_loader/read_object_error.c
	src/object_loader/n_atof.c
	src/object_loader/split_into_tokens.c

	shaders/SimpleVertexShader.glsl
)

TARGET_LINK_LIBRARIES(scop ${ALL_LIBS})

# Xcode and Visual working directories
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
