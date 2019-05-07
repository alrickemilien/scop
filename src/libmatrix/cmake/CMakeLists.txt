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
	src/mat4/look_at_mat4_2.c
	src/mat4/scale_mat4.c
	src/mat4/translate_mat4.c
	src/mat4/perspective_mat4.c
	src/mat4/rotate_mat4.c

	# vec3
	src/vec3/swap_vec3.c
	src/vec3/constant.c
	src/vec3/copy_vec3.c
	src/vec3/is_origin_vec3.c
	src/vec3/normalize_vec3.c
	src/vec3/set_vec3.c
	src/vec3/are_vec3_equal.c
	src/vec3/operations/scale_vec3.c
	src/vec3/operations/magnitude_vec3.c
	src/vec3/operations/dot_product_vec3.c
	src/vec3/operations/substract_vec3.c
	src/vec3/operations/add_vec3.c
	src/vec3/operations/cross_vec3.c

	# Libmatrix
	src/matrix/pmatrix.c
	src/matrix/determinant.c
	src/matrix/minor.c
	src/matrix/identity_matrix.c
	src/matrix/inverse_matrix.c
	src/matrix/compare_matrix.c
	src/matrix/add_matrix.c
	src/matrix/fill_matrix.c
	src/matrix/copy_matrix.c
	src/matrix/new_matrix.c
	src/matrix/new_matrix_from_raw.c
	src/matrix/delete_matrix.c
	src/matrix/matrix_at.c
	src/matrix/multiply_matrix_with_scalar.c
	src/matrix/multiply_matrix.c
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
