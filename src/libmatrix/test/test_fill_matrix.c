#include "test_package.h"
#include "libmatrix.h"

int main(void) {
  t_matrix  *m;

	/****************************************************************************/
	NEW_TEST("basic fill matrix with 1 in order to get :\n"
	"{1, 1, 1, 1}\n"
	"{1, 1, 1, 1}\n"
	"{1, 1, 1, 1}\n"
	"{1, 1, 1, 1}");

	char tmp[100];
	GLfloat val_to_test = 56.3;

  m = new_matrix(4, 4);

	fill_matrix(m, &val_to_test);

	for (size_t i = 0; i < m->lines; i++) {
		for (size_t j = 0; j < m->columns; j++) {
			if (m->value[i * m->columns + j] != val_to_test) {
				sprintf(tmp, "The value at column %ld ans line %ld is not at %lf", i, j, val_to_test);
				FAIL(tmp);
			}
		}
	}

	ALL_OK();
}
