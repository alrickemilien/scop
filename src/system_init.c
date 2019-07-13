#include "scop.h"

/*
** Initialize the system with the provided resources
** - Register the current
** - Find the shader folder and register the path
** - Read the resources into the object folder
** When all ok, start the application
*/

int system_init(t_software_environ *env, int argc, char **argv)
{
	if (argc < 2)
		exit_error_with_message("Input file missing.");

#ifdef __APPLE__
	if (getcwd(env->cwd, sizeof(env->cwd)) == NULL)
		exit_error_with_message("An error occured when oading the pwd path of the program.");
#else
	if (_getcwd(env->cwd, sizeof(env->cwd)) == NULL)
		exit_error_with_message("An error occured when oading the pwd path of the program.");
#endif

	// Load provided object file
	if (load_object_file(&env->data, argv[1]) < 0)
		return (-1);

	// Load mtllib files if any provided
	if (load_mtllib(env->data.mtllib, env->data.usemtl) < 0)
		return (-1);

	env->bmp.buffer = NULL;
	env->tga.buffer = NULL;
	env->tga.image = NULL;
	//if (argc > 2 && load_bitmap_file(&env->bmp, argv[2]) < 0)
	//	return (-1);
	if (argc > 2 && load_tga_file(&env->tga, argv[2]) < 0)
		return (-1);

	count_vertices(&env->data);

	env->scale = 1.0f;
	env->y_auto_rotate_angle = 0.f;
	env->render_style = GL_TRIANGLES;
	env->indexation_mode = env->data.smooth_shading ? 1 : 0;
	env->ambient_lighting = 0.45f;
	env->specular_lighting = 0.5f;
	env->render_normals = false;

	// All OK, start applicaton
	return (0);
}