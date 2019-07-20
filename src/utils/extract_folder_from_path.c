#include "utils.h"
#include <stdio.h>

/*
** This function extract the folder from the provided path
** where it is located.
** =======================================================
** Examples : the binary is executed at /root/
** /path/to/file => /path/to/
** path => /root/
** ./path/to/file => /root/path/to/
** path/to/file => ./path/to/
** /path/to/ => /path/
** ../ => /
** ../../path/to/file => /path/to/
** ./ => /
** . => /
** .. => /
*/

#ifdef __APPLE__

char    *extract_folder_from_path(const char *path)
{
	char *tmp;
	char *ret;

	tmp = strdup(path);

	ret = dirname(tmp);

	free(tmp);

	return (ret);
}
#else
char    *extract_folder_from_path(const char *path)
{
	char dir[_MAX_DIR];

	if (_splitpath_s(path, NULL, 0,    // Don't need drive
	                 dir, sizeof(dir), // Just the directory
	                 NULL, 0,          // Don't need filename
	                 NULL, 0) != 0)
	{
		return (NULL);
	}

	return strdup(dir);
}
#endif
