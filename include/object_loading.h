#ifndef OBJ_LOADING_H
# define OBJ_LOADING_H

# define BUFF_SIZE 512
# define TYPE_COUNT 5
# define DEFAULT_CODE -9

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
}				t_obj_data;

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

int			token_to_int(const char **tokens, int index);
int			are_tokens_enough(const char **tokens, int qty);

typedef struct				s_type_match
{
	const char				*token;
	int						(*f)(const char **);
}							t_type_match;

int							read_vec3(const char **tokens, t_vec3 *vector);
int							read_vec2(const char **tokens, t_vec3 *vector);

int							read_comment(const char **tokens);
int							read_position(const char **tokens);
int							read_color(const char **tokens);
int							read_normal(const char **tokens);
int							read_polygon(const char **tokens);

int							read_line(char *line);

void						reading_die(const char *msg);

int							add_vertex(
								const char **tokens,
								int no_texture,
								t_lst *vertices);

#endif
