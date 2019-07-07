#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# define DEFAULT_CODE -9

# include "loader.h"
# include "material_template_library_loader.h"

/*
** Here are the token utilisties for parsing into .obj files
*/

# define COMMENT_TOKEN "#"
# define POSITION_TOKEN "v"
# define COLOR_TOKEN "vt"
# define NORMAL_TOKEN "vn"
# define FACE_TOKEN "f"
# define NAME_TOKEN "o"
# define MTLLIB_TOKEN "mtllib"
# define USEMTL_TOKEN "usemtl"

// @TODO need to implement this shit
# define SMOOTH_SHADING_AROUND_POLYGON_TOKEN "s"

/*
** In order to reference material
*/

typedef struct			s_usemtl {
	size_t				start;
	size_t				end;
	char				*mtl;

	// Keep NULL until it has not been filled
	t_mtl_data			*material;
}						t_usemtl;

/*
** Struct returned by parse_obj. It contains a list of everything in the file,
** where :
**	- name is the given name, it is not mandatory
**	- mtl is the name of a material template library
**	- positions correspond to 'v'
**	- uvs correspond to 'vt'
**	- normals correspond to 'vn'
**	- polygons correspond to 'f'
*/

typedef struct			s_mesh
{
	char				*name;
	char				*path;
	char				*mtl;
	t_list				*positions;
	t_list				*uvs;
	t_list				*normals;
	
	// A vertex is composed of one position, one uv and one normal
	t_list				*vertices;

	// A polygon is composed of at least 3 vertices
	t_list				*polygons;

	// All texture libs
	t_list				*mtllib;

	// MTL reference of faces
	t_list				*usemtl;

	size_t				vertex_count;
	size_t				faces_count;
	bool				is_texture_set;
	GLint				smooth_shading;
}						t_mesh;

typedef struct			s_polygon {
	t_list				*vertices;

	// Provide storing space for polygon's normal
	t_vec3				normal;
}						t_polygon;

typedef struct			s_vertex
{
	size_t				position_index;
	size_t				color_index;
	size_t				normal_index;
	size_t				uv_index;

	t_vec3				*position;
	t_vec3				*color;
	t_vec2				*uv;
	t_vec2				uv_sphere;
	t_vec3				*normal;
}						t_vertex;

int						is_vec2_defined(t_vec2 *v);
int						is_vec3_defined(t_vec3 *v);

typedef int				(*t_parse_function)(
							t_mesh *m,
							const t_token *t);

typedef struct			s_type_match
{
	const char			*token;
	t_parse_function	f;
}						t_type_match;

/*
** Parse functions
*/

int							load_object_file(t_mesh *data, const char *file_path);

int							read_vec3(const t_token *tokens, t_vec3 *vector);
int							read_vec2(const t_token *tokens, t_vec3 *vector);

int							read_comment(t_mesh *data, const t_token *tokens);
int							read_position(t_mesh *data, const t_token *tokens);
int							read_color(t_mesh *data, const t_token *tokens);
int							read_normal_vector(t_mesh *data, const t_token *tokens);
int							read_face(t_mesh *data, const t_token *tokens);
int							read_name(t_mesh *data, const t_token *tokens);
int							read_usemtl(t_mesh *data, const t_token *tokens);
int							read_mtllib(t_mesh *data, const t_token *tokens);

int							read_vertex(t_mesh *data, const t_token *tokens, t_polygon *polygon);

int							read_object_file_line(t_mesh *data, const char *line);
int							read_smooth_shading(t_mesh *data, const t_token *tokens);

int 						read_object_error(const char *msg);

int							add_vertex(
								t_mesh *data,
								const t_token *tokens,
								int no_texture,
								t_list *vertices);

void						print_object(const t_mesh *data);

int							fill_vertex_position(t_mesh *data, t_vertex *vertex);
int							fill_vertex_color(t_mesh *data, t_vertex *vertex);
int							fill_vertex_normal(t_mesh *data, t_vertex *vertex);

#endif
