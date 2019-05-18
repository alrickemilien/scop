#include "scop.h"

/*
static void	set_light_uniforms(t_software_environ *env)
{
	env->light_position_uni = glGetUniformLocation(env->program_id,
		"lightPosition");

	glUniform3f(
		env->light_position_uni,
		env->light.position.x,
		env->light.position.y,
		env->light.position.z);

	env->light_color_uni = glGetUniformLocation(env->program_id,
		"lightColor");

	glUniform3f(
		env->light_color_uni,
		env->light.color.x,
		env->light.color.y,
		env->light.color.z);
}
*/

/*
** This is the size of memory of polygon vertex
** It is composed of many vertices
** Each vertice is composed of position, color uv and normal
*/

static void load_polygon_into_data(t_polygon *polygon, void *buffer) {
	t_list	*x;
	size_t	i;
	t_vertex	*vertex;

	// t_vec3 color = { 240.f / 255.f, 0.f / 255.f, 0.f / 255.f };

	i = 0;
	x = polygon->vertices;

//	size_t vertex_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);
	size_t vertex_size = sizeof(t_vec3) * 2;

	while (x)
	{
		vertex = (t_vertex*)x->content;

		memcpy((uint8_t*)buffer + i * vertex_size, &vertex->position, sizeof(t_vec3));

		memcpy((uint8_t*)buffer + i * vertex_size + sizeof(t_vec3), &vertex->position, sizeof(t_vec3));

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
}

/*
* * Convert a list into a vbo ( GL vertex buffer object )
*/
static void vertex_list_to_vbo(t_software_environ *env)
{
	size_t		i;
	t_list		*x;
	GLfloat			*buffer;

	// A polygon is three vertex length
	// size_t vertex_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);
	size_t vertex_size = sizeof(t_vec3) * 2;

	size_t polygon_size = 3 * vertex_size;

	buffer = (GLfloat*)malloc(vertex_size * env->data.vertex_count);

	memset(buffer, 0, vertex_size * env->data.vertex_count);

	printf("env->data.vertex_count : %ld\n", env->data.vertex_count);

	// print_object((const void*)&env->data);

	printf("Load Polygons\n");

	i = 0;
	x = env->data.polygons;
	size_t poly_length;
	while (x)
	{
		poly_length = ft_lstlen(((t_polygon*)x->content)->vertices);

		if (poly_length == 3) {
			// Load 3 polygons into data
			load_polygon_into_data(x->content, (GLfloat*)((char*)buffer + i * polygon_size));

			// Increase of three because a polygon is 3 vertex long
			i++;
		}

		x = x->next;
	}

	printf("I resulted to %ld\n", i);

	printf("Load VAO\n");

	if (glGenVertexArrays == NULL) {
		fprintf(stderr, "glGenVertexArrays do not exist, exiting now ...\n");
		exit(-1);
	}

	if (glBindVertexArray == NULL) {
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
	glBufferData(GL_ARRAY_BUFFER,
							polygon_size * i,
							buffer,
							GL_STATIC_DRAW);

	free(buffer);
}

void plan_to_vbo(t_software_environ *env) {
	// Load vao
	glGenVertexArrays(1, &env->plan_vao);
	
	check_gl_error();

	glBindVertexArray(env->plan_vao);

	// Load plan vbo
	//GLfloat *plan_buffer = (GLfloat*)malloc(sizeof(t_vec3) * 2);
	GLfloat *plan_buffer = (GLfloat*)malloc(sizeof(t_vec3));


	t_vec3 v = {0.f, -3.f, 0.f};
	// t_vec3 color = { 165.f / 255.f, 165.f / 255.f, 165.f / 255.f };

	memcpy((uint8_t*)plan_buffer, &v, sizeof(t_vec3));
	// memcpy((uint8_t*)plan_buffer + sizeof(t_vec3), &color, sizeof(t_vec3));

	glGenBuffers(1, &env->plan_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->plan_vbo);
	glBufferData(GL_ARRAY_BUFFER,
							//sizeof(t_vec3) * 2,
							sizeof(t_vec3),							
							plan_buffer,
							GL_STATIC_DRAW);

	free(plan_buffer);
}

void axis_to_vbo(t_software_environ *env) {
	// Load vao
	glGenVertexArrays(1, &env->axis_vao);
	
	check_gl_error();

	glBindVertexArray(env->axis_vao);

	// Load axis vbo
	GLfloat *axis_buffer = (GLfloat*)malloc(sizeof(t_vec3));

	t_vec3 v = {0.f, 0.f, 0.f};

	memcpy((uint8_t*)axis_buffer, &v, sizeof(t_vec3));

	glGenBuffers(1, &env->axis_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->axis_vbo);
	glBufferData(GL_ARRAY_BUFFER,
							sizeof(t_vec3),							
							axis_buffer,
							GL_STATIC_DRAW);

	free(axis_buffer);
}

int	gl_buffering(t_software_environ *env)
{
	// Load vertex only VBO
	vertex_list_to_vbo(env);

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

	gl_matrixing(env);

//	load_texture(env);

//	glUniform1i(env->lighting_uni, env->lighting);

// env->lighting_uni = glGetUniformLocation(env->program_id, "lighting");

//	env->texture_level_uni = glGetUniformLocation(env->program_id, "textureLevel");

//	glUniform1f(env->texture_level_uni, env->texture_level);

//	set_light_uniforms(env);

	return (0);
}
