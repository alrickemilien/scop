#include "libmatrix.h"
#include "test_package.h"

static void raw_to_matrix(t_mat4 *m, const GLfloat *raw)
{
	for (size_t i = 0; i < 16; i++)
		m->value[i] = raw[i];
}

int main(void)
{
	t_mat4 m;
	GLfloat val = 42.0;

	t_mat4 a1;
	t_mat4 a2;
	t_mat4 a_result;

	/****************************************************************************/
	NEW_TEST("basic test pmatrix");

	fill_mat4(&m, &val);

	pmatrix("%lf", &m);

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

	const GLfloat  raw1[] = {
	    8.2,  0.3,  6.0,  85.5, 32.5, 8.0, 100.0, -9.5,
	    66.3, -8.2, 25.0, -6.0, 1.3,  2.0, 53.3,  99,
	};

	const GLfloat  raw2[] = {
	    52.3, -6.3,   -2.0, -10.5, 8.7,  -6.2,  -2.0, 150.0,
	    12.5, -100.0, 85.9, 0.9,   -1.5, -90.5, 0.9,  1.0,
	};

	raw_to_matrix(&a1, (const GLfloat *)raw1);
	raw_to_matrix(&a2, (const GLfloat *)raw2);

	pmatrix("%lf", &a1);
	multiply_to_mat4(&a1, &a2, &a_result);

	/****************************************************************************/
	ALL_OK();
}
