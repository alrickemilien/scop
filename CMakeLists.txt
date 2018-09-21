# CMake version
cmake_minimum_required (VERSION 3.0)

# Project name
project (Scope)

# OPENGL package
find_package(OpenGL REQUIRED)



# Warnig on build directory
if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()

# Warning on src directory name whitespaces
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Warning on build directory name whitespaces
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)


# On Visual 2005 and above, this module can set the debug working directory

cmake_policy(SET CMP0026 OLD)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")

include(CreateLaunchers)

# /MP
include(MSVCMultipleProcessCompile)


# Create distrib subdirectory
if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)


# Includes directory (-I on Makefile)
include_directories(
	external/AntTweakBar-1.16/include/

	external/glfw-3.1.2/include/

	external/glm-0.9.7.1/

	external/glew-1.13.0/include/

	external/assimp-3.0.1270/include/

	external/bullet-2.81-rev2613/src/

	.
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
add_executable(scop
	src/main.cpp
	lib/shader.hpp
	shaders/SimpleVertexShader.vertexshader
)

target_link_libraries(scop
	${ALL_LIBS}

)

# Xcode and Visual working directories

set_target_properties(scop PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")

create_target_launcher(scop WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )

SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


# Xcode things
if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

add_custom_command(
   TARGET src POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/src${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
