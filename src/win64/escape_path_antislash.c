#include "scop.h"

#ifdef _MSC_VER
/*
** Fuck windows
*/

static int		count_char_into_string(const char *str, const char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			n++;
		i++;
	}

	return (n);
}

/*
** This function esacpe all backslashes for windows paths
** "C:\\Users\\Alrick\\scop\\shaders\\SimpleFragmentShader.glsl"
** becomes "C:\\\Users\\\Alrick\\\scop\\\shaders\\\SimpleFragmentShader.glsl"
*/
char*	create_escaped_path_for_windows(const char *path)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (count_char_into_string(path, 0x5C) + strlen(path)));

	if (ret == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (path[i])
	{
		ret[j] = path[i];

		if (path[i] == 0x5C) {
			j++;
			ret[j] = 0x5C;
		}

		i++;
		j++;
	}

	return (ret);
}

#endif