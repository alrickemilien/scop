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
* * This is the size of memory of polygon vertex
* * It is composed of many vertices
* * Each vertice is composed of position, color uv and normal
*/

static void load_polygon_into_data(t_polygon *polygon, void *buffer) {
	t_list	*x;
	size_t	i;
	t_vertex	*vertex;

	t_vec3 color = { 0xFF, 0xFF, 0xFF };

	i = 0;
	x = polygon->vertices;

	size_t vertex_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);

	while (x)
	{
		vertex = (t_vertex*)x->content;

		memcpy((uint8_t*)buffer + i * vertex_size, &vertex->position, sizeof(t_vec3));

		memcpy((uint8_t*)buffer + i * vertex_size + sizeof(t_vec3), &color, sizeof(t_vec3));

		memcpy(
			(uint8_t*)buffer + i * vertex_size + sizeof(t_vec3) + sizeof(t_vec3),
			&vertex->uv,
			sizeof(t_vec2)
		);

		memcpy(
			(uint8_t*)buffer + i * vertex_size + sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2),
			&vertex->normal,
			sizeof(t_vec3)
		);

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
	float			*buffer;

	// A polygon is three vertex length
	size_t vertex_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);
	size_t polygon_size = 3 * vertex_size;


	buffer = (float*)malloc(vertex_size * env->data.vertex_count);

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
			load_polygon_into_data(x->content, buffer + i * polygon_size);

			// Increase of three because a polygon is 3 vertex long
			i++;
		}

		printf("i:%ld\n", i);

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
	printf("ici \n");

	glBindVertexArray(env->vao);

	// 2 - Load VBO

	printf("Load VBO\n");

	glGenBuffers(1, &env->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER,
							polygon_size * env->data.vertex_count,
							buffer,
							GL_STATIC_DRAW);
}

void prepare(t_software_environ *env)
{
	// Load vertex only VBO
	vertex_list_to_vbo(env);

	// Load the vriables taht will be use into shaders
	// the variables id will be stored in env structure
	// with the fields of the same name
	set_attribute(env->program_id, "position");
	set_attribute(env->program_id, "color");
	set_attribute(env->program_id, "uv");
	set_attribute(env->program_id, "normal");

//	load_texture(env);

	env->view_matrix = identity_matrix(4, 4);

	env->model_matrix = scale_matrix4x4(0.2);

	env->projection_matrix = perspective_matrix4x4(
		deg_to_rad(60.0),
		800.0 / 600.0,
		0.0,
		1000.0);

	env->mvp_uni = glGetUniformLocation(env->program_id, "mvp");

//	env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");

//	env->lighting_uni = glGetUniformLocation(env->program_id, "lighting");

//	glUniform1i(env->lighting_uni, env->lighting);

//	env->texture_level_uni = glGetUniformLocation(env->program_id, "textureLevel");

//	glUniform1f(env->texture_level_uni, env->texture_level);

//	set_light_uniforms(env);
}
