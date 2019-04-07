#include "scop.h"

void exit_error_with_message(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(-1);
}
