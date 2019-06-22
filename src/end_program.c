
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

static void clear_env_memory()
{
	t_list	*x;

	printf("Clearing environnement ...\n");

	if (!env)
		return;

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
	x = env->data.usemtl;
	while (x)
	{
		free(((t_usemtl*)x->content)->mtl);
		ft_lstdelone(&x, &del);
		x = x->next;
	}

	// Delete mttlib
	x = env->data.usemtl;
	while (x)
	{
		free(*(char**)x->content);
		ft_lstdelone(&x, &del);
		x = x->next;
	}

	// @TODO ==> need to clear sublist
	if (env->data.polygons)
		ft_lstdel(&env->data.polygons, &del);

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

	glfwTerminate();

	clear_env_memory();

	printf("Closed.\n");

	exit(code);
}