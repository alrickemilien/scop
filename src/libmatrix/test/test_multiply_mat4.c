#include "libmatrix.h"
#include "test_package.h"

static void raw_to_matrix(t_mat4* m, const GLfloat *raw)
{
	for (size_t i = 0; i < 16; i++)
		m->value[i] = raw[i];
}

int main(void)
{
	t_mat4 a1;
	t_mat4 a2;
	t_mat4 a_result;

	char    tmp[1024];
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

	fill_mat4(&a1, &val);
	fill_mat4(&a2, &val);

	multiply_to_mat4(&a1, &a2, &a_result);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (a_result.value[i * 4 + j] != 4)
			{
				sprintf(tmp, "The value at column %ld ans line %ld is not at %lf but is at %lf", i, j, val,
				        a_result.value[i * 4 + j]);
				FAIL(tmp);
			}
		}
	}

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

	const GLfloat raw1[] = {
	    8.2f,  0.3f,  6.0f,  85.5f, 32.5f, 8.0f, 100.0f, -9.5f,
	    66.3f, -8.2f, 25.0f, -6.0f, 1.3f,  2.0f, 53.3f,  99.0f,
	};

	const GLfloat raw2[] = {
	    52.3f, -6.3f,   -2.0f, -10.5f, 8.7f,  -6.2f,  -2.0f, 150.0f,
	    12.5f, -100.0f, 85.9f, 0.9f,   -1.5f, -90.5f, 0.9f,  1.0f,
	};

	const GLfloat raw_result[] = {
	    378.22f,  -8391.27f, 575.35f, 49.8f,     3033.6f, -9394.6f,   8500.45f, 939.25f,
	    3717.65f, -2323.85f, 2025.9f, -1909.65f, 603.14f, -14310.09f, 4660.97f, 433.32f,
	};

	raw_to_matrix(&a1, (const GLfloat *)raw1);
	raw_to_matrix(&a2, (const GLfloat *)raw2);

	multiply_to_mat4(&a1, &a2, &a_result);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (fabs(raw_result[i * 4 + j] - a_result.value[i * 4 + j]) > 0.1f)
			{
				sprintf(tmp, "The value at column %ld ans line %ld is not at %lf but is at %lf ==> diff is %lf", i, j,
				        raw_result[i * 4 + j],
				        a_result.value[i * 4 + j],
				        fabs(raw_result[i * 4 + j] - a_result.value[i * 4 + j]));
				FAIL(tmp);
			}
		}
	}

	/****************************************************************************/
	ALL_OK();
}
