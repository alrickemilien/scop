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
	t_mat4 t;

	char    tmp[1024];
	GLfloat val = 1.0;

	/****************************************************************************/
	NEW_TEST("basic multiply the following matrix\n"
	         "{1, 1, 1, 1}     {1, 1, 1, 1}\n"
	         "{1, 1, 1, 1} T = {1, 1, 1, 1}\n"
	         "{1, 1, 1, 1}     {1, 1, 1, 1}\n"
	         "{1, 1, 1, 1}     {1, 1, 1, 1}\n");

	fill_mat4(&m, &val);

	transpose_to_mat4(&m, &t);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (t.value[i * 4 + j] != 1)
			{
				sprintf(tmp, "The value at column %ld ans line %ld is not at %lf but is at %lf", i, j, val, t.value[i * 4 + j]);
				FAIL(tmp);
			}
		}
	}

	/****************************************************************************/
	NEW_TEST("multiply the following matrix\n"
	         "{ 8.2,  0.3,   6.0, 85.5}     { 8.2,	32.5,	66.3,	1.3, }\n"
	         "{32.5,  8.0, 100.0, -9.5} and { 0.3,	8,	-8.2,	2, }\n"
	         "{66.3, -8.2,  25.0, -6.0}     { 6,	100,	25,	53.3 }\n"
	         "{ 1.3,  2.0,  53.3,   99}     { 85.5,	-9.5,	-6,	99,}\n");

	const GLfloat raw[] = {
	    8.2f,  0.3f,  6.0f,  85.5f, 32.5f, 8.0f, 100.0f, -9.5f,
	    66.3f, -8.2f, 25.0f, -6.0f, 1.3f,  2.0f, 53.3f,  99.0f,
	};

	const GLfloat raw_result[] = {
	    8.2f, 32.5f,  66.3f, 1.3f,  0.3f,  8.0f,  -8.2f, 2.0f,
	    6.0f, 100.0f, 25.0f, 53.3f, 85.5f, -9.5f, -6.0f, 99.0f,
	};

	raw_to_matrix(&m, (const GLfloat *) raw);
	raw_to_matrix(&t, (const GLfloat *) raw_result);

	transpose_to_mat4(&m, &t);

	printmat4(&m);
	printf("\n");
	printmat4(&t);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (fabs(raw_result[i * 4 + j] - t.value[i * 4 + j]) > 0.1f)
			{
				sprintf(tmp, "The value at column %ld ans line %ld is not at %lf but is at %lf ==> diff is %lf", i, j, raw_result[i * 4 + j], t.value[i * 4 + j], fabs(raw_result[i * 4 + j] - t.value[i * 4 + j]));
				FAIL(tmp);
			}
		}
	}

	/****************************************************************************/
	ALL_OK();
}
