# CMake version
cmake_minimum_required (VERSION 3.0)

SET(LIB libmatrix)

# Sets the src directory
SET ( CMAKE_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../
)

SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/../
)

SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/../
)

# Includes directory (-I on Makefile)
INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}include
)

SET (SRC
	# libmatrix internals utils
	src/utils/libmatrix_utils.c
	src/utils/libmatrix_stringutils.c
	src/utils/libmatrix_utils_xtoa.c

	# mat4
	src/mat4/mat4.c
	src/mat4/look_at_mat4.c
	src/mat4/scale_mat4.c
	src/mat4/translate_mat4.c
	src/mat4/perspective_mat4.c
	src/mat4/rotate_mat4.c
	src/mat4/pmatrix.c
	src/mat4/add_mat4.c
	src/mat4/fill_mat4.c
	src/mat4/multiply_mat4.c
	src/mat4/mat4_on_vec3.c
	src/mat4/printmat4.c

	# vec3
	src/vec3/swap_vec3.c
	src/vec3/constant.c
	src/vec3/copy_vec3.c
	src/vec3/is_origin_vec3.c
	src/vec3/normalize_vec3.c
	src/vec3/set_vec3.c
	src/vec3/are_vec3_equal.c
	src/vec3/magnitude_vec3.c
	src/vec3/operations/scale_vec3.c
	src/vec3/operations/dot_product_vec3.c
	src/vec3/operations/sub_vec3.c
	src/vec3/operations/add_vec3.c
	src/vec3/operations/cross_vec3.c

	# vec2
	src/vec2/vec2.c
)

LIST(TRANSFORM SRC PREPEND ${CMAKE_SOURCE_DIR})

# Library name
ADD_LIBRARY( ${LIB} STATIC ${SRC})

if(MSVC)
	#SET_TARGET_PROPERTIES(${LIB} PROPERTIES COMPILE_FLAGS "/Wall /WX" )
	#SET_TARGET_PROPERTIES(${TEST_EXE} PROPERTIES COMPILE_FLAGS "" )
else()
   # add_compile_options("-Wall" "-Wextra")
endif()
