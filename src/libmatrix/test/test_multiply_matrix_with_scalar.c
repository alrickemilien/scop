#include "test_package.h"
#include "libmatrix.h"

int main(void) {
  t_matrix  *m;

	/****************************************************************************/
	NEW_TEST("basic multiply the following matrix\n"
	"{1, 1, 1, 1}\n"
	"{1, 1, 1, 1}\n"
	"{1, 1, 1, 1}\n"
	"{1, 1, 1, 1}\n"
	"with 2");
	
	char tmp[100];
	GLfloat val = 1.0;

  m = new_matrix(4, 4);

	fill_matrix(m, &val);

	multiply_matrix_with_scalar(m, 2);

	for (size_t i = 0; i < m->lines; i++) {
		for (size_t j = 0; j < m->columns; j++) {
			if (m->value[i * m->columns + j] != val * 2) {
				sprintf(tmp, "The value at column %ld ans line %ld is not at %lf", i, j, val);
				FAIL(tmp);
			}
		}
	}

	ALL_OK();
}
