#include "test_package.h"
#include "libmatrix.h"

int main(void) {
  t_matrix  *m;

	/****************************************************************************/
	NEW_TEST("basic test new_matrix(4, 4)");

  m = new_matrix(4, 4);

	if (m == NULL)
		FAIL("matrix is NULL");

	/****************************************************************************/
	NEW_TEST("basic test new_matrix(0, 0)");

	m = new_matrix(0, 4);

	if (m != NULL)
		FAIL("matrix mus be NULL for 0 size");

	ALL_OK();
}
