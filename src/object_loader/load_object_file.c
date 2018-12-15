#include <stdio.h>
#include "object_loading.h"

static size_t				g_current_line;
t_obj_data					*g_current_data;

static int		init_parser(t_obj_data *data)
{
	g_current_line = 0;
	g_current_data = data;

	data->positions = NULL;
	data->uvs = NULL;
	data->normals = NULL;
	data->polygons = NULL;

	return (0);
}

int		load_object_file(t_obj_data *data, const char *file_path)
{
	FILE		*fp;
	char		line[OBJECT_LOADING_BUFF_SIZE];

	if (!(fp = fopen(file_path, "r")) || init_parser(data) < 0) {
		return (-1);
	}

	while (fgets(line, BUFF_SIZE, fp) != NULL && ++g_current_line)
	{
		if (line[0] == '\n')
			continue ;

		if (read_object_file_line(data, line) < 0)
			return (-1);
	}

	fclose(fp);

	return (0);
}
