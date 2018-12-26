#ifndef OBJ_LOADING_H
# define OBJ_LOADING_H

# define OBJECT_LOADING_BUFF_SIZE 512
# define TYPE_COUNT 5
# define DEFAULT_CODE -9

#include <stdlib.h>

# include "libft.h"
# include "libmatrix.h"

/*
** Struct returned by parse_obj. It contains a list of everything in the file,
** where :
**	- positions correspond to 'v' ;
**	- uvs correspond to 'vt' ;
**	- normals correspond to 'vn' ;
**	- polygons correspond to 'f' ;
*/
typedef struct	s_obj_data
{
	void		*positions;
	void		*uvs;
	void		*normals;
	void		*polygons;
	size_t	count_vertices;
}				t_obj_data;

typedef struct s_polygon {
			void *vertices;
}								t_polygon;

typedef struct	s_vertex
{
	t_vec3		position;
	t_vec3		color;
	t_vec2		uv;
	t_vec3		normal;
}				t_vertex;

typedef struct	s_token {
								char *cursor;
								size_t size;
}								t_token;

/*
** Use this function to retrieve data from a obj file path.
** Return values : the t_obj_data structure filled with everything the file
** contains or NULL if an error occured.
*/
t_obj_data		*obj_parse(const char *file_path);

/*
** Use this function to print all data. Very ugly.
*/
void			obj_print_data(const t_obj_data *data);

/*
** Use this function to free all space allocated by obj_parse.
*/
void			obj_delete_data(t_obj_data **data);
int				is_vec2_defined(t_vec2 *v);
int				is_vec3_defined(t_vec3 *v);

/*
** Tokens
*/

# define COMMENT_TOKEN "#"
# define POSITION_TOKEN "v"
# define COLOR_TOKEN "vt"
# define NORMAL_TOKEN "vn"
# define POLYGON_TOKEN "f"

int			token_to_int(const t_token *tokens, size_t index);
bool		check_tokens_number(const t_token *tokens, size_t size);
bool 		is_printable(char c);
t_token *split_into_tokens(const char *line, const char *delimiters);
float		n_atof(const char* str, size_t size);

typedef int	(*t_parse_function)(t_obj_data *, const t_token *);

typedef struct				s_type_match
{
	const char				*token;
	t_parse_function	f;
}							t_type_match;

int							load_object_file(t_obj_data *data, const char *file_path);

int							read_vec3(const t_token *tokens, t_vec3 *vector);
int							read_vec2(const t_token *tokens, t_vec3 *vector);

int							read_comment(t_obj_data *data, const t_token *tokens);
int							read_position(t_obj_data *data, const t_token *tokens);
int							read_color(t_obj_data *data, const t_token *tokens);
int							read_normal_vector(t_obj_data *data, const t_token *tokens);
int							read_polygon(t_obj_data *data, const t_token *tokens);

int							read_vertex(t_obj_data *data, const t_token *tokens, bool is_texture_set, t_polygon *polygon);

int							read_object_file_line(t_obj_data *data, const char *line);

void 						read_object_error(const char *msg);

int							add_vertex(
								t_obj_data *data,
								const t_token *tokens,
								int no_texture,
								t_list *vertices);

#endif
