#include "scop.h"

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

static const size_t polygon_size = sizeof(t_vec3) * 3 + sizeof(t_vec2);

static void load_polygon_into_data(t_polygon *polygon, void *buffer) {
	t_list	*x;
	size_t	i;
	t_vertex	*vertex;

	i = 0;
	x = polygon->vertices;

	while (x)
	{
		vertex = (t_vertex*)x->content;

		memcpy(buffer + i * polygon_size, &vertex->position, sizeof(t_vec3));

		memcpy(buffer + i * polygon_size + sizeof(t_vec3), &vertex->color, sizeof(t_vec3));

		memcpy(
			buffer + i * polygon_size + sizeof(t_vec3) + sizeof(t_vec2),
			&vertex->uv,
			sizeof(t_vec2)
		);

		memcpy(
			buffer + i * polygon_size + sizeof(t_vec3) + sizeof(t_vec3) + sizeof(t_vec2),
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
	size_t		buffer_length;
	t_list		*x;
	float			*buffer;

	buffer_length = 11 * env->data.vertex_count;

	buffer = (float*)calloc(buffer_length, sizeof(float));

	i = 0;

	x = env->data.polygons;
	while (x)
	{
		load_polygon_into_data(x->content, buffer + i * polygon_size);

		// Increase of three because a polygon is 3 vertex long
		i += 3;

		x = x->next;
	}

	printf("a\n");

	// 1 - Load VBO

	glGenBuffers(1, &env->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer_length * sizeof(float), buffer,
		GL_STATIC_DRAW);
	// 2 - Load into VAO
	printf("b\n");

	// Here initiate the VAO
	// It sets an unsigned integer to identify it with later
	glGenVertexArrays(1, &env->vao);

	printf("c\n");
	// bind it, to bring it in to focus in the state machine
	glBindVertexArray(env->vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);

	printf("d\n");
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	printf("e\n");

	printf("f\n");


// 	/**
// 	** Okay, so we created a vertex array object,
// 	** and described 1 attribute "pointers" within it.
// 	** Attributes are disabled by default in OpenGL 4. We need to explicitly enable them too.
// 	** This is easy to get wrong or overlook, and is not well explained in the documentation.
// 	** We use a function called glEnableVertexAttribArray() to enable each one.
// 	** This function only affects the currently bound vertex array object.
// 	** This means that when we do this now, it will only affect our attributes, above.
// 	** We will need to bind every new vertex array and repeat this procedure for those too.
// We are using 2 attributes (points and colours), and we know that these are numbered 0 (points), and 1 (colours); matching the numbers we gave when setting up the vertex attribute pointers, earlier.
// 	*/
//
// 	glEnableVertexAttribArray(0);
}

void prepare(t_software_environ *env)
{
	printf("1\n");
	// Load vertex only VBO
	vertex_list_to_vbo(env);

	printf("2\n");
	// Load the vriables taht will be use into shaders
	// the variables id will be stored in env structure
	// with the fields of the same name
	set_attribute(env->program_id, "position");
	set_attribute(env->program_id, "color");
	set_attribute(env->program_id, "uv");
	set_attribute(env->program_id, "normal");

	load_texture(env);

	printf("3\n");
	env->view_matrix = identity_matrix(4, 4);
	printf("4\n");
	env->model_matrix = scale_matrix4x4(0.2);
	printf("5\n");
	env->projection_matrix = perspective_matrix4x4(
		deg_to_rad(60.0),
		800.0 / 600.0,
		0.0,
		1000.0);

		printf("6\n");
	env->mvp_uni = glGetUniformLocation(env->program_id, "mvp");
	env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");
	env->lighting_uni = glGetUniformLocation(env->program_id, "lighting");

	glUniform1i(env->lighting_uni, env->lighting);

	env->texture_level_uni = glGetUniformLocation(env->program_id, "textureLevel");

	glUniform1f(env->texture_level_uni, env->texture_level);

	set_light_uniforms(env);

}
