
#include "scop.h"

extern t_software_environ	*g_env;

static bool					closing = false;

/*
** Clear the environnement in memory
*/

static void del(void *p, size_t s)
{
	(void)s;
	free(p);
}

/*
** Clear the environnement in memory
*/

static void	del_usemtl(void *p, size_t s)
{
	t_usemtl	*u;

	(void) s;
	u = (t_usemtl *) p;
	free(u->mtl);
	free(u);
}

/*
** Clear the environnement in memory
*/

static void	del_vertex(void *p, size_t s)
{
	t_vertex	*vertex;

	(void)s;
	vertex = (t_vertex *) p;
	free(vertex);
}

/*
** Clear the environnement in memory
*/

static void	del_polygon(void *p, size_t s)
{
	t_polygon	*polygon;

	(void)s;
	polygon = (t_polygon *) p;
	ft_lstdel(&polygon->vertices, &del_vertex);
	free(polygon);
}

static void	clear_env_memory()
{
	printf("Clearing environnement ...\n");

	if (!g_env)
		return ;

	printf("A\n");

	// Destory texture memory buffer
	if (g_env->texture.is_texture_loaded)
		free(g_env->texture.data);

	printf("B\n");
	if (g_env->data.name)
		free(g_env->data.name);
	printf("C\n");
	if (g_env->data.mtl)
		free(g_env->data.mtl);
	printf("D\n");
	if (g_env->data.positions)
		ft_lstdel(&g_env->data.positions, &del);
	printf("=E\n");
	if (g_env->data.uvs)
		ft_lstdel(&g_env->data.uvs, &del);
	printf("F\n");
	if (g_env->data.normals)
		ft_lstdel(&g_env->data.normals, &del);
	if (g_env->data.uvs)
		ft_lstdel(&g_env->data.uvs, &del);

	printf("G\n");
	// Delete usemtl
	ft_lstdel(&g_env->data.usemtl, &del_usemtl);

	printf("H\n");
	// Delete mtllib
	ft_lstdel(&g_env->data.mtllib, &del);

	printf("I\n");
	// @TODO ==> need to clear sublist
	if (g_env->data.polygons)
		ft_lstdel(&g_env->data.polygons, &del_polygon);

	printf("J\n");
	free(g_env);
}

// Close OpenGL window and terminate GLFW
void		end_program(int code)
{
	if (closing)
		return;

	closing = true;

	printf("Closing app ...\n");

	cleanup_shader_program(&g_env->object_shader_program);
	cleanup_shader_program(&g_env->internal_object_shader_program);

	glDeleteBuffers(1, &g_env->vbo);
	glDeleteBuffers(1, &g_env->plan_vbo);
	glDeleteBuffers(1, &g_env->axis_vbo);

	if (g_env->indexation_mode)
		glDeleteBuffers(1, &g_env->ebo);

	glDeleteVertexArrays(1, &g_env->vao);
	glDeleteVertexArrays(1, &g_env->plan_vao);
	glDeleteVertexArrays(1, &g_env->axis_vao);

	if (g_env->texture.is_texture_loaded)
		glDeleteTextures(1, &g_env->texture_uni);

	glfwTerminate();

	clear_env_memory();

	printf("Closed.\n");

	exit(code);
}