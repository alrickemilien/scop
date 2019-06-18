#include "material_template_library_loader.h"

int		load_mtl_file(t_mtl_list data, const char *mtl_file_path)
{
	FILE		*fp;
	char		line[LOADER_LINE_BUFF_SIZE];
	size_t		g_current_line;

	g_current_line = 0;

	memset(data, 0, sizeof(t_mtl_list));

	if (!(fp = fopen(mtl_file_path, "r")))
		return (-1);

	while (fgets(line, BUFF_SIZE, fp) != NULL && ++g_current_line)
	{
		if (line[0] == '\n')
			continue ;

		if (read_mtl_file_line(data, line) < 0)
			return (-1);
	}

	fclose(fp);

	return (0);
}
