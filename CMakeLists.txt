# CMake version
cmake_minimum_required (VERSION 3.0)

# OPENGL package
find_package(OpenGL REQUIRED)

# Sets the src directory
set ( CMAKE_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/
)

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Compile external dependencies
add_subdirectory (external/glfw)

add_subdirectory (external/glew)

add_subdirectory (src/libmatrix/cmake)

# Includes directory (-I on Makefile)
include_directories(
	external/glfw/include/GLFW/

	external/glew/include/

	include/

	src/libmatrix/include/
)

# Library to use (-l on Makefile)
if(WIN32)
	set(ALL_LIBS
		${OPENGL_LIBRARY}

		glfw

		lib/Debug/glewd

		src/libmatrix/Debug/libmatrix
	)
else()
	set(ALL_LIBS
		${OPENGL_LIBRARY}

		glfw

		external/glew/lib/glewd

		src/libmatrix
	)
endif()

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set (WIN_SOURCES
	src/win64/load_single_shader.c
	src/win64/strndup.c
)

set (OSX_SOURCES
	src/shader/load_single_shader.c
)

set (SOURCES
    #
    # scop core functions library
    #
    src/core/render.c
    src/core/render_meshs_normals.c
    src/core/render_mesh.c
    src/core/render_mesh.c
    src/core/is_vertex_same.c
    src/core/apply_rotation.c
	src/core/gl_lighting.c
	src/core/gl_attribute.c
	src/core/gl_buffering.c
	src/core/check_gl_error.c
	src/core/gl_log.c
	src/core/exit_error_with_msg.c
	src/core/gl_matrixing.c
	src/core/count_vertices.c
	src/core/compute_vertex_normal.c
	src/core/compute_mvp.c
	src/core/math_utils.c
	src/core/gl_indexing.c
	src/core/gl_texturing.c
    src/core/compute_vertex_uvs.c
    src/core/smart_camera_position.c
    
    #
    # Shader
    #
	src/shader/print_shader_error.c
	src/shader/load_single_shader.c
	src/shader/load_program_shader.c
	src/shader/cleanup_shader_program.c
    src/shader/compile_shader.c
    
    #
    # BMP files
    #
	src/texture_loader/bmp/load_bitmap_file.c
    src/texture_loader/bmp/load_bitmap_file_header.c
    
    #
    # TGA files
    #
    src/texture_loader/tga/load_tga_file.c
    src/texture_loader/tga/utils.c
    src/texture_loader/tga/decode_tga.c
    src/texture_loader/tga/fill_tga_header.c
    src/texture_loader/load_texture_file.c

    #
    # Controls and toggle of the app
    #
	src/controls/close.c
	src/controls/controls.c
	src/controls/light.c
	src/controls/lock.c
	src/controls/move.c
	src/controls/render.c
	src/controls/resize.c
	src/controls/scale.c
	src/controls/unlock.c

    #
    # .obj loader
    #
    src/object_loader/read_position.c
    src/object_loader/read_comment.c
    src/object_loader/read_smooth_shading.c
    src/object_loader/read_uv.c
    src/object_loader/print_token.c
    src/object_loader/read_object_file_line.c
    src/object_loader/read_vertex.c
    src/object_loader/read_mtllib.c
    src/object_loader/read_vec2.c
    src/object_loader/read_vec3.c
    src/object_loader/read_normal_vector.c
    src/object_loader/read_name.c
    src/object_loader/load_object_file.c
    src/object_loader/print_object.c
    src/object_loader/read_usemtl.c
    src/object_loader/read_object_error.c
    src/object_loader/read_face.c

    #
    # .mtl loader
    #
    src/mtl_loader/read_mtl_error.c
    src/mtl_loader/read_dissolved.c
    src/mtl_loader/read_specular_color.c
    src/mtl_loader/load_mtl_file.c
    src/mtl_loader/read_illumination.c
    src/mtl_loader/read_mtl_file_line.c
    src/mtl_loader/read_comment.c
    src/mtl_loader/read_ambient_color.c
    src/mtl_loader/read_diffuse_color.c
    src/mtl_loader/read_optical_density.c
    src/mtl_loader/read_transparency.c
    src/mtl_loader/read_new_mtl.c
    src/mtl_loader/load_mtllib.c
    src/mtl_loader/load_mtl_file.c
	src/mtl_loader/read_mtl_file_line.c
	src/mtl_loader/read_new_mtl.c
	src/mtl_loader/read_comment.c

    #
    # Loader utils
    #
    src/loader_utils/utils.c
    src/loader_utils/split_whitespaces.c
    src/loader_utils/n_atof.c
    src/loader_utils/split_into_tokens.c
    src/loader_utils/n_atoi.c

    #
    # Logs
    #
    src/core/gl_log.c

    #
    # Utils
    #
    src/utils/ft_strjoin.c
	src/utils/ft_lstindex.c
	src/utils/ft_lstadd.c
	src/utils/lst_data_at.c
	src/utils/ft_lstlen.c
	src/utils/ft_lstnew.c
	src/utils/ft_lstdel.c
	src/utils/ft_lstreverse.c
	src/utils/ft_lstdelone.c
	src/utils/ft_lstfind.c
    src/utils/extract_folder_from_path.c
        
    src/main.c
    src/run.c
	src/glfw_init.c
	src/system_init.c
	src/end_program.c
)

list(TRANSFORM SOURCES PREPEND ${CMAKE_SOURCE_DIR})

# Create the executable
if(WIN32)
	ADD_EXECUTABLE(scop
		${SOURCES}
		${WIN_SOURCES}
	)
else()
	ADD_EXECUTABLE(scop
		${SOURCES}
		${OSX_SOURCES}
	)
endif()

TARGET_LINK_LIBRARIES(scop ${ALL_LIBS})

# Xcode and Visual working directories
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
