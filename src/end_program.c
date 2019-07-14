
#include "scop.h"

extern t_software_environ *env;

static bool closing = false;

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

static void del_usemtl(void *p, size_t s)
{
	t_usemtl *u;

	(void)s;
	u = (t_usemtl*)p;
	free(u->mtl);
	free(u);
}


/*
** Clear the environnement in memory
*/

static void del_vertex(void *p, size_t s)
{
	t_vertex	*vertex;

	(void)s;
	vertex = (t_vertex*)p;
	free(vertex->uv);
	free(vertex);
}

/*
** Clear the environnement in memory
*/

static void del_polygon(void *p, size_t s)
{
	t_polygon	*polygon;

	(void)s;
	polygon = (t_polygon*)p;
	ft_lstdel(&polygon->vertices, &del_vertex);
	free(polygon);
}

static void clear_env_memory()
{
	printf("Clearing environnement ...\n");

	if (!env)
		return;

	// Destory texture memory buffer
	if (env->texture.is_texture_loaded)
		free(env->texture.data);

	if (env->data.name)
		free(env->data.name);

	if (env->data.mtl)
		free(env->data.mtl);

	if (env->data.positions)
		ft_lstdel(&env->data.positions, &del);
	
	if (env->data.uvs)
		ft_lstdel(&env->data.uvs, &del);
	
	if (env->data.normals)
		ft_lstdel(&env->data.normals, &del);

	// Delete usemtl
	ft_lstdel(&env->data.usemtl, &del_usemtl);

	// Delete mtllib
	ft_lstdel(&env->data.mtllib, &del);

	// @TODO ==> need to clear sublist
	if (env->data.polygons)
		ft_lstdel(&env->data.polygons, &del_polygon);

	free(env);
}

// Close OpenGL window and terminate GLFW
void end_program(int code)
{
	if (closing)
		return ;

	closing = true;

	printf("Closing app ...\n");

	cleanup_shader_program(&env->object_shader_program);
	cleanup_shader_program(&env->internal_object_shader_program);

	glDeleteBuffers(1, &env->vbo);
	glDeleteBuffers(1, &env->plan_vbo);
	glDeleteBuffers(1, &env->axis_vbo);

	if (env->indexation_mode)
		glDeleteBuffers(1, &env->ebo);

	glDeleteVertexArrays(1, &env->vao);
	glDeleteVertexArrays(1, &env->plan_vao);
	glDeleteVertexArrays(1, &env->axis_vao);

	glDeleteTextures(1, &env->texture_uni);

	glfwTerminate();

	clear_env_memory();

	printf("Closed.\n");

	exit(code);
}