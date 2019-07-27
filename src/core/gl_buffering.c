#include "scop.h"

const size_t vertex_size_g = sizeof(t_vec3) * 3 + sizeof(t_vec2);

/*
** This is the size of memory of polygon vertex
** It is composed of many vertices
** Each vertice is composed of position, color uv and normal
*/

static void	load_polygon_into_data(t_software_environ *env, t_polygon *polygon, void *buffer)
{
	t_list		*x;
	size_t		i;
	t_vertex	*vertex;
	t_vec3		normal;
	t_vec2		*uv;

	t_vec3 color = {1.0f, 1.0f, 1.0f};
	t_vec2 uvs[3] = {
	    {0.0f, 0.0f}, // lower-left corner
	    {1.0f, 0.0f}, // lower-right corner
	    {0.5f, 1.0f}, // top-center corner
	};

	i = 0;
	x = polygon->vertices;

	while (x)
	{
		vertex = (t_vertex *) x->content;

		memcpy((uint8_t *) buffer + i * vertex_size_g, vertex->position, sizeof(t_vec3));

		memcpy((uint8_t *) buffer + i * vertex_size_g + sizeof(t_vec3), &color, sizeof(t_vec3));

		if (vertex->normal == NULL)
		{
			compute_vertex_normal(&env->data, vertex, &normal);
			vertex->normal = &normal;
		}

		memcpy((uint8_t *) buffer + i * vertex_size_g + sizeof(t_vec3) + sizeof(t_vec3),
		       vertex->normal, sizeof(t_vec3));

		uv = vertex->uv == NULL ? &uvs[i % 3] : vertex->uv;

		memcpy((uint8_t *) buffer + i * vertex_size_g + sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec3), uv, sizeof(t_vec2));

		i++;

		x = x->next;
	}
}

/*
 * * Convert a list into a vbo ( GL vertex buffer object )
 */
static void	vertex_list_to_vbo(t_software_environ *env)
{
	size_t	i;
	t_list	*x;
	GLfloat	*buffer;
	size_t	poly_length;

	// A polygon is three vertex length

	buffer = (GLfloat *) malloc(vertex_size_g * env->data.vertex_count);

	memset(buffer, 0, vertex_size_g * env->data.vertex_count);

	printf("env->data.vertex_count : %ld\n", env->data.vertex_count);

	// print_object((const void*)&env->data);

	printf("Load Polygons\n");

	i = 0;
	x = env->data.polygons;
	while (x)
	{
		poly_length = ft_lstlen(((t_polygon *) x->content)->vertices);

		load_polygon_into_data(env, x->content, (GLfloat *) ((char *) buffer + i));

		i += vertex_size_g * poly_length;

		x = x->next;
	}

	printf("I resulted to %ld\n", i);

	printf("Load VAO\n");

	if (glGenVertexArrays == NULL)
	{
		fprintf(stderr, "glGenVertexArrays do not exist, exiting now ...\n");
		exit(-1);
	}

	if (glBindVertexArray == NULL)
	{
		fprintf(stderr, "glBindVertexArray do not exist, exiting now ...\n");
		exit(-1);
	}

	// 1 - Load VAO

	glGenVertexArrays(1, &env->vao);

	check_gl_error();

	glBindVertexArray(env->vao);

	// 2 - Load VBO

	printf("Load VBO\n");

	glGenBuffers(1, &env->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, i, buffer, GL_STATIC_DRAW);

	free(buffer);
}

void		plan_to_vbo(t_software_environ *env)
{
	t_vec3	v;
	GLfloat	*plan_buffer;
	
	v = (t_vec3){0.f, -3.f, 0.f};

	// Load vao
	glGenVertexArrays(1, &env->plan_vao);

	check_gl_error();

	glBindVertexArray(env->plan_vao);

	// Load plan vbo
	// GLfloat *plan_buffer = (GLfloat*)malloc(sizeof(t_vec3) * 2);
	plan_buffer = (GLfloat *) malloc(sizeof(t_vec3));

	// t_vec3 color = { 165.f / 255.f, 165.f / 255.f, 165.f / 255.f };

	memcpy((uint8_t *) plan_buffer, &v, sizeof(t_vec3));
	// memcpy((uint8_t*)plan_buffer + sizeof(t_vec3), &color, sizeof(t_vec3));

	glGenBuffers(1, &env->plan_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->plan_vbo);
	glBufferData(GL_ARRAY_BUFFER,
	             // sizeof(t_vec3) * 2,
	             sizeof(t_vec3), plan_buffer, GL_STATIC_DRAW);

	free(plan_buffer);
}

void		axis_to_vbo(t_software_environ *env)
{
	t_vec3	v;
	GLfloat	*axis_buffer;
	
	v = (t_vec3){0.f, 0.f, 0.f};

	// Load vao
	glGenVertexArrays(1, &env->axis_vao);

	check_gl_error();

	glBindVertexArray(env->axis_vao);

	// Load axis vbo
	axis_buffer = (GLfloat*) malloc(sizeof(t_vec3));

	memcpy((uint8_t*)axis_buffer, &v, sizeof(t_vec3));

	glGenBuffers(1, &env->axis_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->axis_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3), axis_buffer, GL_STATIC_DRAW);

	free(axis_buffer);
}

int			gl_buffering(t_software_environ *env)
{
	// Load vertex only VBO
	vertex_list_to_vbo(env);

	printf("env->object_shader_program.id, : %d\n", env->object_shader_program.id);

	// Load the vriables taht will be use into shaders
	// the variables id will be stored in env structure
	// with the fields of the same name
	if (set_attribute(env->object_shader_program.id, "position", vertex_size_g) < 0)
		return (-1);
	if (set_attribute(env->object_shader_program.id, "color", vertex_size_g) < 0)
		return (-1);
	if (set_attribute(env->object_shader_program.id, "normal", vertex_size_g) < 0)
		return (-1);
	if (set_attribute(env->object_shader_program.id, "uv", vertex_size_g) < 0)
		return (-1);

	plan_to_vbo(env);

	if (set_attribute(env->internal_object_shader_program.id, "position", sizeof(t_vec3)) < 0)
		return (-1);

	axis_to_vbo(env);

	if (set_attribute(env->axis_shader_program.id, "position", sizeof(t_vec3)) < 0)
		return (-1);

	return (0);
}
