#include <stdlib.h>
#include <stdio.h>
#include "object_loading.h"

static size_t				g_current_line;
t_obj_data					*g_current_data;

static const t_type_match	g_type_matches[] = {
	{
		COMMENT_TOKEN,
		parse_comment,
	},
	{
		POSITION_TOKEN,
		parse_position,
	},
	{
		COLOR_TOKEN,
		parse_color,
	},
	{
		NORMAL_TOKEN,
		parse_normal,
	},
	{
		POLYGON_TOKEN,
		parse_polygon
	},
	{
		NULL,
		NULL
	}
};

static int		init_parser(t_obj_data *data)
{
	g_current_line = 0;
	g_current_data = data;

	data->positions = NULL;
	data->uvs = NULL;
	data->normals = NULL;
	data->polygons = NULL;

	return (1);
}

t_obj_data		*load_object_file(const char *file_path)
{
	FILE		*fp;
	char		line[BUFF_SIZE];
	t_obj_data	*data;

	if (!(fp = fopen(file_path, "r"))
		|| !(data = (t_obj_data*)malloc(sizeof(t_obj_data)))
		|| !init_parser(data))
		return (NULL);

	while (fgets(line, BUFF_SIZE, fp) != NULL && ++g_current_line)
	{
		if (line[0] == '\n')
			continue ;

		if (!parse_line(line))
			return (NULL);
	}

	fclose(fp);

	return (data);
}
