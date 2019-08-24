#include "libmatrix.h"

void	printmat4(const t_mat4 *m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
			printf("%.3f ", m->value[j++ * 4 + i]);
		printf("\n");
		i++;
	}
	printf("\n");
}
