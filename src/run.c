/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:05:55 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:08:14 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** This macro handles the fact that windows
** works with \ and not / as Unix
** when it comes to treat with files ...
*/

static const char	*g_vertex_file_path = "/shaders/mesh/"
"VertexShader.glsl";
static const char	*g_fragment_file_path = "/shaders/mesh/"
"FragmentShader.glsl";
static const char	*g_plan_vertex_file_path = "/shaders/plan/"
"VertexShader.glsl";
static const char	*g_plan_fragment_file_path = "/shaders/plan/"
"FragmentShader.glsl";
static const char	*g_plan_geometry_file_path = "/shaders/plan/"
"GeometryShader.glsl";
static const char	*g_axis_vertex_file_path = "/shaders/axis/"
"VertexShader.glsl";
static const char	*g_axis_fragment_file_path = "/shaders/axis/"
"FragmentShader.glsl";
static const char	*g_axis_geometry_file_path = "/shaders/axis/"
"GeometryShader.glsl";
static const char	*g_normals_vertex_file_path = "/shaders/normals/"
"VertexShader.glsl";
static const char	*g_normals_fragment_file_path = "/shaders/normals/"
"FragmentShader.glsl";
static const char	*g_normals_geometry_file_path = "/shaders/normals/"
"GeometryShader.glsl";

static void			prepare_load_all_shaders(
		t_software_environ *env)
{
	memset(&env->object_shader_program, 0, sizeof(shader_program_t));
	memset(&env->internal_object_shader_program, 0, sizeof(shader_program_t));
	memset(&env->axis_shader_program, 0, sizeof(shader_program_t));
	memset(&env->normals_shader_program, 0, sizeof(shader_program_t));
	env->object_shader_program.cwd = (char *)env->cwd;
	env->internal_object_shader_program.cwd = (char *)env->cwd;
	env->axis_shader_program.cwd = (char *)env->cwd;
	env->normals_shader_program.cwd = (char *)env->cwd;
}

static void			load_all_shaders(
		t_software_environ *env)
{
	prepare_load_all_shaders(env);
	if (load_program_shader(
				&env->object_shader_program,
				g_vertex_file_path,
				g_fragment_file_path,
				NULL) < 0)
		end_program(-1);
	if (load_program_shader(
				&env->internal_object_shader_program,
				g_plan_vertex_file_path,
				g_plan_fragment_file_path,
				g_plan_geometry_file_path) < 0)
		end_program(-1);
	if (load_program_shader(
				&env->axis_shader_program,
				g_axis_vertex_file_path,
				g_axis_fragment_file_path,
				g_axis_geometry_file_path) < 0)
		end_program(-1);
	if (load_program_shader(
				&env->normals_shader_program,
				g_normals_vertex_file_path,
				g_normals_fragment_file_path,
				g_normals_geometry_file_path) < 0)
		end_program(-1);
}

/*
** Check if the ESC key was pressed or the window was closed
** wipe the drawing surface clear
** Handle other events (mouse, keyboard, ...)
** Swap buffers
*/

static void			render_loop(
		t_software_environ *env)
{
	while (glfwWindowShouldClose(env->window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(env);
		glfwPollEvents();
		glfwSwapBuffers(env->window);
	}
}

void				run(
		t_software_environ *env)
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClearColor(SCOP_BACKGROUND);
	printf("About to fill load program shader ...\n");
	load_all_shaders(env);
	printf("About to fill uvs ...\n");
	fill_uvs(env->data.polygons);
	printf("About to start buffering ...\n");
	if (!env->indexation_mode && gl_buffering(env) < 0)
		end_program(-1);
	if (env->indexation_mode && gl_indexing(env) < 0)
		end_program(-1);
	check_gl_error();
	gl_matrixing(env);
	check_gl_error();
	gl_texturing(env);
	check_gl_error();
	gl_lighting(env);
	check_gl_error();
	printf("Preparation is done\n");
	render_loop(env);
	end_program(0);
}
