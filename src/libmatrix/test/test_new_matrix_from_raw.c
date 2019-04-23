#include "test_package.h"
#include "libmatrix.h"

int main(void) {
  t_matrix  *m;

	/****************************************************************************/
	NEW_TEST("new matrix from raw data float");

	char tmp[100];
	const GLfloatraw[] = {
		85.5, 88.9, -36, 0,
		7.2, 52.8, 0.5, 0.0003,
		80, 1000.0001, 42, 0,
		0, 0, 63.3, 1.0,
	};

	m = new_matrix_from_raw((const GLfloat*) raw, 4, 4);

	for (size_t i = 0; i < m->lines; i++) {
		for (size_t j = 0; j < m->columns; j++) {
			if (m->value[i * m->columns + j] != raw[i * m->columns + j]) {
				sprintf(tmp,
					"The value at column %ld ans line %ld is not at %lf but at %lf",
					i, j, raw[i * m->columns + j], m->value[i * m->columns + j]);
				FAIL(tmp);
			}
		}
	}

	ALL_OK();
}
