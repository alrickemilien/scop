#include "object_loader.h"

/*
** Convert string of size n into float
*/

float n_atof(const char* str, size_t size)
{
  float  ret;
	float  negate;
	int 	 point_seen;
	size_t i;
	int		 digit;

	ret = 0;

	negate = 1;
	if (str[0] == '-') {
    str++;
    negate = -1;
  }

	i = 0;
	point_seen = -1;
	while (i < size && str[i]) {
		if (str[i] == '.'){
			point_seen = i;
		} else {
			digit = str[i] - '0';

			if (digit >= 0 && digit <= 9) {
				if (point_seen > -1) {

					ret +=  powf(0.1f, i - point_seen) * (float)digit;
				} else {
					ret = ret * 10.0f + (float)digit;
				}
			} else {
				break;
			}
		}

		i++;
	}

	return (ret * negate);
}
