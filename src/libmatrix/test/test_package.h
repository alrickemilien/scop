#ifndef TEST_PACKAGE_H
# define TEST_PACKAGE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

void test_warning(const char *msg);
void test_failure(const char *msg);
void test_log_step(const char *msg);
void test_finished(void);

#define NEW_TEST(x) test_log_step(x)

#define FAIL(x) test_failure(x)

#define WARING(x) test_warning(x)

#define ALL_OK() test_finished()

#endif
