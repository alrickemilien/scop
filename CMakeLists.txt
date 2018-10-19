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
add_subdirectory (external)


# Create distrib subdirectory
if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

# Includes directory (-I on Makefile)
include_directories(
	external/glfw-3.1.2/include/

	external/glew-1.13.0/include/

	include/
)

# Library to use (-l on Makefile)
set(ALL_LIBS
	${OPENGL_LIBRARY}

	glfw

	GLEW_1130
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
	
	src/lib/shader.h
	src/lib/create_triangle.c
	src/lib/load_shaders.c
	
	shaders/SimpleVertexShader.glsl
)

TARGET_LINK_LIBRARIES(scop
	${ALL_LIBS}
)

# Xcode and Visual working directories
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
