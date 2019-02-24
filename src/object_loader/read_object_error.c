# include "object_loader.h"

int read_object_error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	return (-1);
}
