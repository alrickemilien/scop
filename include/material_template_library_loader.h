#ifndef MATERIAL_TEMPLATE_LIBRARY_LOADER_LOADER_H
# define MATERIAL_TEMPLATE_LIBRARY_LOADER_LOADER_H

# include <stdlib.h>
# include <stdio.h>

# include "libmatrix.h"
# include "loader.h"

/*
** Here are the token utilisties for parsing into .mtl files
** exmqple of mtl file :
** newmtl None
** Ns 0
** Ka 0.000000 0.000000 0.000000
** Kd 0.8 0.8 0.8
** Ks 0.8 0.8 0.8
** d 1
** illum 2
*/

# define COMMENT_TOKEN "#"
# define NEWMTL_TOKEN "newmtl"
# define AMBIENT_COLOR_TOKEN "Ka"
# define DIFFUSE_COLOR_TOKEN "Kd"
# define SPECULAR_COLOR_TOKEN "Ks"
# define SPECULAR_COLOR_EXPONENT_TOKEN "Ns"
# define DISSOLVED_TOKEN "d"
# define TRANSPARENCY_TOKEN "Tr"
# define ILLUMINATION_TOKEN "illum"

typedef struct				s_mtllib {
	char					*path;
	t_list					*materials_list;
}							t_mtllib;

/*
** Struct returned by parse_mlt
*/

typedef struct				s_mtl_data
{
	char					*label;
	float					ambient;
	float					diffuse;
	float					specular;
	float					dissolved;
	float					transparency;
	float					illumination;
}							t_mtl_data;

typedef int					(*t_mtl_parse_function)(
								t_mtllib *l,
								t_mtl_data *material,
								const t_token *t);

typedef struct				s_mtl_type_match
{
	const char				*token;
	t_mtl_parse_function	f;
}							t_mtl_type_match;

int							read_mtl_file_line(
								t_mtllib *lib,
								const char *line);
int							read_mtl_comment(
								t_mtllib *lib,
								t_mtl_data *material,
								const t_token *tokens);
int							read_new_mtl(
								t_mtllib *lib,
								t_mtl_data *material,
								const t_token *tokens);
int							read_specular_color_exponent(
								t_mtllib *lib,
								t_mtl_data *material,
								const t_token *tokens);

int							load_mtllib(t_list *mtllib);
int							load_mtl_file(t_mtllib *data);

#endif
