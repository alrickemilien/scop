#include "test_package.h"

/*
** Test countdown
*/

static int test_inc = 0;

void test_warning(const char *msg) {
	printf("Test %d WARNING : %s\n", test_inc, msg);
}

void test_failure(const char *msg) {
	printf("Test %d FAILED : %s\n", test_inc, msg);
	exit(-1);
}

void test_log_step(const char *msg) {
	if (test_inc > 0)
		printf("Test %d PASSED\n", test_inc);

	test_inc++;
	printf("==> Test %d : %s\n", test_inc, msg);
}

void test_finished(void) {
		printf("All tests pass\n");
}

bool are_floating_point_equal(GLfloat a, GLfloat b, GLfloat precision) {
	if (fabs(a - b) <= precision)
		return (true);

	return false;
}
