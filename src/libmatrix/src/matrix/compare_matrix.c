#include "libmatrix.h"

bool compare_matrix(t_matrix *a, t_matrix *b)
{
  if (a->columns != b->columns || a->lines != b->lines)
    return (false);

  if (memcmp(a->value, b->value, sizeof(uint64_t) * a->columns * a->lines) != 0)
    return (false);

  return (true);
}
