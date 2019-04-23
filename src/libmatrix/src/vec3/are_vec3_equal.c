#include "libmatrix.h"

inline int				are_vec3_equal(const t_vec3 *vector1, const t_vec3 *vector2)
{
	if (memcmp(vector1, vector2, sizeof(t_vec3)))
    return (false);

  return (true);
}
