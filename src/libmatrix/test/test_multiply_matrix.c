#include "test_package.h"
#include "libmatrix.h"

int main(void) {
  t_matrix  *a1;
  t_matrix  *a2;
  t_matrix  *a_result;

	char tmp[100];
	GLfloat val = 1.0;

	/****************************************************************************/
	NEW_TEST("basic multiply the following matrix\n"
	"{1, 1, 1, 1}     {1, 1, 1, 1}\n"
	"{1, 1, 1, 1} and {1, 1, 1, 1}\n"
	"{1, 1, 1, 1}     {1, 1, 1, 1}\n"
	"{1, 1, 1, 1}     {1, 1, 1, 1}\n"
	"The result should be :\n"
	"{4, 4, 4, 4}\n"
	"{4, 4, 4, 4}\n"
	"{4, 4, 4, 4}\n"
	"{4, 4, 4, 4}");

  a1 = new_matrix(4, 4);
  a2 = new_matrix(4, 4);
  a_result = new_matrix(4, 4);

	fill_matrix(a1, &val);
	fill_matrix(a2, &val);

	multiply_matrix(a1, a2, a_result);

	for (size_t i = 0; i < a_result->lines; i++) {
		for (size_t j = 0; j < a_result->columns; j++) {
			if (a_result->value[i * a_result->columns + j] != 4) {
				sprintf(tmp,
					"The value at column %ld ans line %ld is not at %lf but is at %lf",
					i, j, val, a_result->value[i * a_result->columns + j]);
				FAIL(tmp);
			}
		}
	}

	delete_matrix(a1);
	delete_matrix(a2);
	delete_matrix(a_result);

	/****************************************************************************/
	NEW_TEST("multiply the following matrix\n"
	"{ 8.2,  0.3,   6.0, 85.5}     { 52.3,   -6.3, -2.0, -10.5 }\n"
	"{32.5,  8.0, 100.0, -9.5} and {  8.7,   -6.2, -2.0, 150.0 }\n"
	"{66.3, -8.2,  25.0, -6.0}     { 12.5, -100.0, 85.9,   0.9 }\n"
	"{ 1.3,  2.0,  53.3,   99}     { -1.5,  -90.5,  0.9,   1.0 }\n"
	"The result should be :\n"
	"{  378.22,  -8391.27,  575.35,    49.8  }\n"
	"{ 3033.6 ,  -9394.6 , 8500.45,   939.25 }\n"
	"{ 3717.65,  -2323.85, 2025.9 , -1909.65 }\n"
	"{  603.14, -14310.09, 4660.97,   433.32 }");

	const GLfloatraw1[] = {
		8.2, 0.3, 6.0, 85.5,
		32.5, 8.0, 100.0, -9.5,
		66.3, -8.2, 25.0, -6.0,
		1.3, 2.0, 53.3, 99,
	};

	const GLfloatraw2[] = {
		52.3, -6.3, -2.0, -10.5,
		8.7, -6.2, -2.0, 150.0,
		12.5, -100.0, 85.9, 0.9,
		-1.5, -90.5, 0.9, 1.0,
	};

	const GLfloatraw_result[] = {
		378.22, -8391.27, 575.35, 49.8,
		3033.6, -9394.6,8500.45, 939.25,
		3717.65, -2323.85, 2025.9, -1909.65,
		603.14, -14310.09, 4660.97, 433.32,
	};

	a1 = new_matrix_from_raw((const GLfloat*) raw1, 4, 4);
	a2 = new_matrix_from_raw((const GLfloat*) raw2, 4, 4);
	a_result = new_matrix(4, 4);

	multiply_matrix(a1, a2, a_result);

	for (size_t i = 0; i < a_result->lines; i++) {
		for (size_t j = 0; j < a_result->columns; j++) {
			if (are_floating_point_equal(a_result->value[i * a_result->columns + j], raw_result[i * a_result->columns + j], 0.1))
			{
				sprintf(tmp,
					"The value at column %ld ans line %ld is not at %lf but is at %lf ==> diff is %lf",
					i, j, raw_result[i * a_result->columns + j], a_result->value[i * a_result->columns + j], fabs(raw_result[i * a_result->columns + j] - a_result->value[i * a_result->columns + j]));
				FAIL(tmp);
			}
		}
	}

	delete_matrix(a1);
	delete_matrix(a2);
	delete_matrix(a_result);

	/****************************************************************************/
	ALL_OK();
}
