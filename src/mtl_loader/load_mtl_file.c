/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mtl_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:19:38 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:19:39 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	load_mtl_file(t_mtllib *data)
{
	FILE	*fp;
	char	line[LOADER_LINE_BUFF_SIZE];
	size_t	g_current_line;

	g_current_line = 0;
	if (!(fp = fopen(data->path, "r")))
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
