#include "object_loader.h"
#include <math.h>

static int	is_negative(const char *str)
{
	int	negate;

	negate = 1;
	if (str[0] == '-')
		negate = -1;
	return (negate);
}

/*
** Convert string of size n into integer
*/

int			n_atoi(const char *str, size_t size)
{
	int	ret;
	int	negate;
	int	i;
	int	digit;

	ret = 0;
	if ((negate = is_negative(str)))
		str++;
	i = 0;
	while (i < (int)size && str[i])
	{
		digit = str[i] - '0';
		if (digit >= 0 && digit <= 9)
			ret = ret * 10 + (int)digit;
		else
			break ;
		i++;
	}
	return (ret * negate);
}
