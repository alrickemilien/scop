#include <stdio.h>
#include "object_loading.h"

static size_t				g_current_line;

int		load_object_file(t_obj_data *data, const char *file_path)
{
	FILE		*fp;
	char		line[OBJECT_LOADING_BUFF_SIZE];

	memset(data, 0, sizeof(t_obj_data));

	if (!(fp = fopen(file_path, "r"))) {
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
