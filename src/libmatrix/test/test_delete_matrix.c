#include "test_package.h"
#include "libmatrix.h"

int main(void) {
  t_matrix  *m;

	/****************************************************************************/
	NEW_TEST("basic delete a matrix(4, 4)");

  m = new_matrix(4, 4);

	delete_matrix(m);

	/****************************************************************************/
	ALL_OK();
}
