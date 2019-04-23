#include <stdio.h>

#include "libmatrix.h"

int main(void) {
  t_matrix  *m;
  t_matrix  *t;
  t_matrix  *n;
  void      *value;

  m = new_matrix(4, 4);

  value = matrix_at(m, 0, 0);
  ((t_matrix_data_type*)value)->fvalue = 1.0f;
  value = matrix_at(m, 1, 1);
  ((t_matrix_data_type*)value)->fvalue = 1.0f;
  value = matrix_at(m, 2, 2);
  ((t_matrix_data_type*)value)->fvalue = 1.0f;
  value = matrix_at(m, 3, 3);
  ((t_matrix_data_type*)value)->fvalue = 1.0f;

  multiply_matrix_with_fscalar(m, 2.5f);

  pmatrix("%f", m);

  printf("get_fdeterminant(m) : %f\n", get_fdeterminant(m));

  get_transpose(m, &t);

  pmatrix("%f", t);

  fill_matrix(t, &((t_matrix_data_type*)value)->fvalue);

  pmatrix("%f", t);
  multiply_matrix_with_fscalar(t, 100.0f);
  pmatrix("%f", t);

  printf("get_fdeterminant(m) : %f\n", get_fdeterminant(m));

  uint64_t raw[4][4] = {
    {0.1f, 0.2f, 0.3f, 0.4f},
    {0.1f, 0.2f, 0.3f, 0.4f},
    {0.1f, 0.2f, 0.3f, 0.4f},
    {0.1f, 0.2f, 0.3f, 0.4f},
  };

  n = new_matrix_from_raw((const uint64_t**)raw, 4, 4);
  pmatrix("%f", n);
  printf("get_fdeterminant(m) : %f\n", get_fdeterminant(n));
//  itoa_hex(45, &bytes, 16);

//  printf("%s\n", bytes);

  delete_matrix(m);
}
