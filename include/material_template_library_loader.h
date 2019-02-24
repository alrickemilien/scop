#ifndef MATERIAL_TEMPLATE_LIBRARY_LOADER_LOADER_H
# define MATERIAL_TEMPLATE_LIBRARY_LOADER_LOADER_H

# include <stdlib.h>
# include <stdio.h>

# include "libft.h"
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

/*
** Struct returned by parse_mlt
*/

typedef struct	s_mtl_data
{
	char					*label;
	float					ambient;
	float					diffuse;
	float					specular;
	float					dissolved;
	float					transparency;
	float					illumination;
}								t_mtl_data;

typedef t_list** t_mtl_list;

typedef int	(*t_parse_function)(t_mtl_list, const t_token *);

typedef struct			s_type_match
{
	const char				*token;
	t_parse_function	f;
}										t_type_match;

int			read_mtl_file_line(t_mtl_list data, const char *line);

int			read_mtl_comment(t_mtl_list data, const t_token *tokens);
int				read_new_mtl(t_mtl_list data, const t_token *tokens);

#endif
