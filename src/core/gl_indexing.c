#include "scop.h"

/*
** Provides VBO indexing style functions
** may be slower to setup but same perf on render
** and more accurate on render
*/

static void vertex_list_to_vbo(t_software_environ *env)
{
	size_t		i;
	t_list		*x;
	GLfloat		*buffer;
	t_vertex	*vertex;

	// A polygon is three vertex length
	// size_t vertex_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);
	size_t vertex_size = sizeof(t_vec3) * 2;

	buffer = (GLfloat*)malloc(vertex_size * ft_lstlen(env->data.vertices));

	memset(buffer, 0, vertex_size * ft_lstlen(env->data.vertices));

	printf("Load vertex into vbo\n");

	i = 0;
	x = env->data.vertices;
	while (x)
	{
		vertex = (t_vertex*)x->content;

		t_vec3 *u = vertex->position;

		printf("BARYCENTRE : .x %f .y %f .z %f \n", u->x, u->y, u->z);

		memcpy((uint8_t*)buffer + i * vertex_size, vertex->position, sizeof(t_vec3));

		memcpy((uint8_t*)buffer + i * vertex_size + sizeof(t_vec3), vertex->position, sizeof(t_vec3));

		//	memcpy(
		//		(uint8_t*)buffer + i * vertex_size + sizeof(t_vec3) + sizeof(t_vec3),
		//		&vertex->uv,
		//		sizeof(t_vec2)
		//	);

		//	memcpy(
		//		(uint8_t*)buffer + i * vertex_size + sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2),
		//		&vertex->normal,
		//		sizeof(t_vec3)
		//	);

		i++;
		x = x->next;
	}

	printf("I resulted to %ld vertices into VBO buffer loading\n", i);

	// 2 - Load VBO
	printf("Load VBO\n");
	glGenBuffers(1, &env->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER,
							i * sizeof(t_vec3) * 2,
							buffer,
							GL_STATIC_DRAW);
	
	free(buffer);	
}

static bool is_vertex_same(const void *a, const void *b) {
	t_vertex *va;
	t_vertex *vb;

	va = (t_vertex*)a;
	vb = (t_vertex*)b;
	
	if (va->position_index == vb->position_index)
		return true;

	return false;
}

/*
** This is the size of memory of polygon vertex
** It is composed of many vertices
** Each vertice is composed of position, color uv and normal
*/

static void load_polygon_into_index_buffer(t_software_environ *env, t_polygon *polygon, void *index_buffer)
{
	t_list		*x;
	size_t		i;
	GLuint		index;

	i = 0;
	x = polygon->vertices;
	while (x)
	{
		index = (GLuint)ft_lstindex(env->data.vertices, x->content, &is_vertex_same);

		if (index == (GLuint)-1)
			printf("%s\n", "HEEEEEIN ???");

		memcpy(
			(uint8_t*)index_buffer + i * sizeof(GLuint),
			// Look for the index of the vertex into list			
			&index,
			sizeof(GLuint));

		i++;
		x = x->next;
	}
}

/*
* * Convert a list into a ebo ( GL vertex buffer object )
*/
static void vertex_list_to_ebo(t_software_environ *env)
{
	size_t		i;
	size_t		j;
	t_list		*x;
	GLuint		*index_buffer;
	size_t		poly_length;

	size_t index_size = sizeof(GLuint);

	index_buffer = (GLuint*)malloc(env->data.vertex_count * index_size);

	memset(index_buffer, 0, env->data.vertex_count * index_size);

	printf("Load index of vertex\n");

	i = 0;
	j = 0;
	x = env->data.polygons;
	while (x)
	{
		poly_length = ft_lstlen(((t_polygon*)x->content)->vertices);
		
		load_polygon_into_index_buffer(env, x->content, (GLuint*)((uint8_t*)index_buffer + i));

		i += index_size * poly_length;
		j++;

		x = x->next;
	}

	printf("I resulted to %ld vertices into ebo buffering\n", i / index_size);
	printf("I resulted to %ld 5polygons into ebo buffering\n", j);

	printf("env->data.vertex_count : %ld\n", env->data.vertex_count);

	printf("Load EBO\n");

    // 3 - Load EBO
	glGenBuffers(1, &env->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
							i,
							index_buffer,
							GL_STATIC_DRAW);

	free(index_buffer);
}

static void vertex_list_to_vao(t_software_environ *env)
{
	if (glGenVertexArrays == NULL) {
		fprintf(stderr, "glGenVertexArrays do not exist, exiting now ...\n");
		exit(-1);
	}

	if (glBindVertexArray == NULL) {
		fprintf(stderr, "glBindVertexArray do not exist, exiting now ...\n");
		exit(-1);
	}

	// 1 - Load VAO
	printf("Load VAO\n");
	glGenVertexArrays(1, &env->vao);
	check_gl_error();
	glBindVertexArray(env->vao);

	// 2 - Load VBO
	vertex_list_to_vbo(env);

	// 3 - Load EBO
	vertex_list_to_ebo(env);
}

int	gl_indexing(t_software_environ *env)
{
	// Load vertex only EBO
	vertex_list_to_vao(env);

	// Load the vriables taht will be use into shaders
	// the variables id will be stored in env structure
	// with the fields of the same name
	if (set_attribute(env->object_shader_program.id, "position", sizeof(t_vec3) * 2) < 0)
		return(-1);
	if (set_attribute(env->object_shader_program.id, "color", sizeof(t_vec3) * 2) < 0)
		return(-1);

	// if (set_attribute(env->object_shader_program.id, "uv") < 0)
	// 	return(-1);
	// if (set_attribute(env->object_shader_program.id, "normal") < 0)
	// 	return(-1);

	plan_to_vbo(env);

	if (set_attribute(env->internal_object_shader_program.id, "position", sizeof(t_vec3)) < 0)
		return(-1);

	axis_to_vbo(env);

	if (set_attribute(env->axis_shader_program.id, "position", sizeof(t_vec3)) < 0)
		return(-1);
	
	return (0);
}