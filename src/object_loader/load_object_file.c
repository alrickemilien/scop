#include <stdio.h>
#include "object_loading.h"

static size_t				g_current_line;

static void	count_vertices(t_obj_data *data)
{
	size_t	count;
	size_t	poly_length;
	t_list	*iter;

	iter = (t_list*)data->polygons;
	count = 0;
	while (iter)
	{
		poly_length = ft_lstlen(((t_polygon*)iter->content)->vertices);
		if (poly_length != 3)
			read_object_error("Scop can only handle triangle shapes.");

		count += poly_length;

		iter = iter->next;
	}

	data->count_vertices = count;
}

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

	count_vertices(data);

	return (0);
}
