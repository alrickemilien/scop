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
* * Each vertice is composed of position color uv and normal
*/

/*
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
*/
/*
* * Convert a list into a vbo ( GL vertex buffer object )
*/
static void vertex_list_to_vbo(t_software_environ *env)
{
	/*
	size_t		i;
	t_list		*x;
	float			*buffer;

	buffer = (float*)malloc(polygon_size * env->data.vertex_count);

	memset(buffer, 0, polygon_size * env->data.vertex_count);

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
*/
	GLfloat points[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };

	GLfloat colors[] = {
  	1.0f, 0.0f,  0.0f,
  	0.0f, 1.0f,  0.0f,
  	0.0f, 0.0f,  1.0f
	};

	// 1 - Load VAO

	glGenVertexArrays(1, &env->vao);
	glBindVertexArray(env->vao);

	// 2 - Load VBO

	GLuint vbo = 0;
	/* a vertex buffer object (VBO) is created here. this stores an array of
	data on the graphics adapter's memory. in our case - the vertex points */
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( GLfloat ), points, GL_STATIC_DRAW );

	/* "attribute #0 should be enabled when this vao is bound" */
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	/* "attribute #0 is created from every 3 variables in the above buffer, of type
	float (i.e. make me vec3s)" */
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );

	// 3 - Load VBO color

	GLuint colours_vbo = 0;
	glGenBuffers(1, &colours_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, NULL);

	glEnableVertexAttribArray(1);

	// 	/**
	// 	** Okay, so we created a vertex array object,
	// 	** and described 1 attribute "pointers" within it.
	// 	** Attributes are disabled by default in OpenGL 4. We need to explicitly enable them too.
	// 	** This is easy to get wrong or overlook, and is not well explained in the documentation.
	// 	** We use a function called glEnableVertexAttribArray() to enable each one.
	// 	** This function only affects the currently bound vertex array object.
	// 	** This means that when we do this now, it will only affect our attributes, above.
	// 	** We will need to bind every new vertex array and repeat this procedure for those too.
	// We are using 2 attributes (points and colors), and we know that these are numbered 0 (points), and 1 (colours); matching the numbers we gave when setting up the vertex attribute pointers, earlier.
	// 	*/

	printf("f\n");

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
//	set_attribute(env->program_id, "position");
//	set_attribute(env->program_id, "color");
//	set_attribute(env->program_id, "uv");
//	set_attribute(env->program_id, "normal");

//	load_texture(env);

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

//	env->mvp_uni = glGetUniformLocation(env->program_id, "mvp");
//	env->model_matrix_uni = glGetUniformLocation(env->program_id, "modelMatrix");
//	env->lighting_uni = glGetUniformLocation(env->program_id, "lighting");

//	glUniform1i(env->lighting_uni, env->lighting);

//	env->texture_level_uni = glGetUniformLocation(env->program_id, "textureLevel");

//	glUniform1f(env->texture_level_uni, env->texture_level);

//	set_light_uniforms(env);

}
