/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:06:48 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:07:58 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Initialize the system with the provided resources
** - Register the current
** - Find the shader folder and register the path
** - Read the resources into the object folder
** When all ok, start the application
*/

int	system_init(t_software_environ *env, int argc, char **argv)
{
	if (argc < 2)
		exit_error_with_message("Input file missing.");
	if (getcwd(env->cwd, sizeof(env->cwd)) == NULL)
		exit_error_with_message(
				"An error occured when loading prog's pwd path");
	if (load_object_file(&env->data, argv[1]) < 0)
		return (-1);
	if (load_mtllib(env->data.mtllib, env->data.usemtl) < 0)
		return (-1);
	if (load_texture_file(&env->texture, argc > 2 ? argv[2] : NULL) < 0)
		return (-1);
	count_vertices(&env->data);
	env->scale = 1.0f;
	env->render_style = GL_TRIANGLES;
	env->indexation_mode = env->data.smooth_shading ? 1 : 0;
	env->ambient_lighting = 0.45f;
	env->specular_lighting = 0.5f;
	env->render_normals = false;
	env->mesh_offset = (t_vec3){0, 0, 0};
	return (0);
}
